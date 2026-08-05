package com.example.flutter_app

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.provider.OpenableColumns
import io.flutter.embedding.android.FlutterActivity
import io.flutter.embedding.engine.FlutterEngine
import io.flutter.plugin.common.MethodChannel
import java.io.File
import java.io.FileOutputStream

class MainActivity : FlutterActivity() {

    private external fun initJuceContext(context: android.content.Context)

    private val PICK_REQUEST = 9001
    private var pendingResult: MethodChannel.Result? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        System.loadLibrary("wtracks_engine")
        initJuceContext(this.applicationContext)
    }

    override fun configureFlutterEngine(flutterEngine: FlutterEngine) {
        super.configureFlutterEngine(flutterEngine)

        MethodChannel(flutterEngine.dartExecutor.binaryMessenger, "wtracks/file_picker")
            .setMethodCallHandler { call, result ->
                if (call.method == "pickAndImport") {
                    if (pendingResult != null) {
                        result.error("BUSY", "Picker already active", null)
                        return@setMethodCallHandler
                    }

                    pendingResult = result

                    val intent = Intent(Intent.ACTION_OPEN_DOCUMENT).apply {
                        addCategory(Intent.CATEGORY_OPENABLE)
                        type = "audio/*"
                        putExtra(Intent.EXTRA_ALLOW_MULTIPLE, true)
                    }

                    startActivityForResult(intent, PICK_REQUEST)
                } else {
                    result.notImplemented()
                }
            }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)

        if (requestCode != PICK_REQUEST) return

        val result = pendingResult ?: return
        pendingResult = null

        if (resultCode != Activity.RESULT_OK || data == null) {
            result.success(emptyList<String>())
            return
        }

        val uriList = mutableListOf<android.net.Uri>()

        data.clipData?.let { clip ->
            for (i in 0 until clip.itemCount) {
                clip.getItemAt(i)?.uri?.let { uriList.add(it) }
            }
        } ?: data.data?.let { uriList.add(it) }

        val imported = mutableListOf<String>()

        for (uri in uriList) {
            // obtain display name
            var name = "file"
            contentResolver.query(uri, null, null, null, null)?.use { cursor ->
                val nameIndex = cursor.getColumnIndex(OpenableColumns.DISPLAY_NAME)
                if (cursor.moveToFirst() && nameIndex != -1) {
                    name = cursor.getString(nameIndex)
                }
            }

            val outFile = File(cacheDir, "wtracks_import/${name}")
            outFile.parentFile?.mkdirs()

            contentResolver.openInputStream(uri)?.use { input ->
                FileOutputStream(outFile).use { output ->
                    input.copyTo(output)
                }
            }

            imported.add(outFile.absolutePath)
        }

        result.success(imported)
    }
}