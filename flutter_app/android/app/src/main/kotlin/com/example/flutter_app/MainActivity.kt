package com.example.flutter_app

import android.Manifest
import android.content.pm.PackageManager
import android.os.Build
import android.app.Activity
import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.provider.OpenableColumns
import io.flutter.embedding.android.FlutterActivity
import io.flutter.embedding.engine.FlutterEngine
import io.flutter.plugin.common.MethodChannel
import java.io.File
import java.io.FileOutputStream
import kotlin.concurrent.thread

class MainActivity : FlutterActivity() {

    private external fun initJuceContext(context: android.content.Context)

    private var pendingResult: MethodChannel.Result? = null
    private val PICK_FILES_REQUEST_CODE = 1001
    private val NOTIFICATION_REQUEST_CODE = 1002
    private var permissionResult: MethodChannel.Result? = null

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

                    try {
                        // Usa a Intent clássica para abrir o seletor de arquivos do Android
                        val intent = Intent(Intent.ACTION_OPEN_DOCUMENT).apply {
                            addCategory(Intent.CATEGORY_OPENABLE)
                            type = "audio/*"
                            putExtra(Intent.EXTRA_ALLOW_MULTIPLE, true)
                        }
                        startActivityForResult(intent, PICK_FILES_REQUEST_CODE)
                    } catch (e: Exception) {
                        pendingResult = null
                        result.error("LAUNCH_FAILED", e.message, e.toString())
                    }
                } else {
                    result.notImplemented()
                }
            }

            // Adicione isso no seu configureFlutterEngine, logo abaixo do channel do file_picker
        MethodChannel(flutterEngine.dartExecutor.binaryMessenger, "wtracks/background").setMethodCallHandler { call, result ->
            if (call.method == "requestNotificationPermission") {
                val prefs = getPreferences(MODE_PRIVATE)
                if (Build.VERSION.SDK_INT >= 33 &&
                    checkSelfPermission(Manifest.permission.POST_NOTIFICATIONS) != PackageManager.PERMISSION_GRANTED &&
                    !prefs.getBoolean("notificationPermissionAsked", false)) {
                    prefs.edit().putBoolean("notificationPermissionAsked", true).apply()
                    permissionResult = result
                    requestPermissions(arrayOf(Manifest.permission.POST_NOTIFICATIONS), NOTIFICATION_REQUEST_CODE)
                } else {
                    result.success(null)
                }
            } else if (call.method == "start") {
                val title = call.argument<String>("title") ?: "WTracks"
                val intent = Intent(this, PlaybackService::class.java).apply {
                    putExtra("title", title)
                }
                if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                    startForegroundService(intent)
                } else {
                    startService(intent)
                }
                result.success(null)
            } else if (call.method == "stop") {
                stopService(Intent(this, PlaybackService::class.java))
                result.success(null)
            } else {
                result.notImplemented()
            }
        }
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == NOTIFICATION_REQUEST_CODE) {
            permissionResult?.success(null) // Denial must never prevent playback.
            permissionResult = null
        }
    }

    // Recebe o resultado do seletor clássico
    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        if (requestCode == PICK_FILES_REQUEST_CODE) {
            if (resultCode == Activity.RESULT_OK && data != null) {
                val uris = mutableListOf<Uri>()
                
                // Trata seleção múltipla
                if (data.clipData != null) {
                    val count = data.clipData!!.itemCount
                    for (i in 0 until count) {
                        uris.add(data.clipData!!.getItemAt(i).uri)
                    }
                } 
                // Trata seleção única
                else if (data.data != null) {
                    uris.add(data.data!!)
                }
                
                handlePickResult(uris)
            } else {
                // Usuário cancelou
                handlePickResult(emptyList())
            }
        } else {
            super.onActivityResult(requestCode, resultCode, data)
        }
    }

    private fun handlePickResult(uris: List<Uri>?) {
        val result = pendingResult
        pendingResult = null

        if (result == null) return

        if (uris.isNullOrEmpty()) {
            result.success(emptyList<String>())
            return
        }

        // Roda a cópia numa thread paralela para não travar a UI!
        thread(name = "wtracks-import") {
            try {
                val imported = mutableListOf<String>()
                val batchDir = File(cacheDir, "wtracks_import/${System.nanoTime()}").apply { mkdirs() }

                for ((index, uri) in uris.withIndex()) {
                    var name: String? = null
                    contentResolver.query(uri, null, null, null, null)?.use { cursor ->
                        val nameIndex = cursor.getColumnIndex(OpenableColumns.DISPLAY_NAME)
                        if (cursor.moveToFirst() && nameIndex != -1) name = cursor.getString(nameIndex)
                    }

                    // Cada arquivo vai para a sua própria pasta: dois URIs com o mesmo nome de exibição (pastas diferentes)
                    // não se sobrescrevem, e o nome do provedor nunca vira caminho (sem "/", "..", controle).
                    val outFile = File(File(batchDir, index.toString()).apply { mkdirs() }, safeFileName(name))

                    contentResolver.openInputStream(uri)?.use { input ->
                        FileOutputStream(outFile).use { output ->
                            input.copyTo(output)
                        }
                    } ?: throw java.io.IOException("openInputStream retornou null para $uri")

                    imported.add(outFile.absolutePath)
                }

                // Devolve o sucesso para a Main Thread do Flutter
                Handler(Looper.getMainLooper()).post {
                    result.success(imported)
                }
            } catch (e: Exception) {
                Handler(Looper.getMainLooper()).post {
                    result.error("IMPORT_FAILED", e.message, e.toString())
                }
            }
        }
    }
}

/** Nome de arquivo seguro a partir do DISPLAY_NAME de um provedor: só o último componente, sem controle nem pontos nas pontas. */
internal fun safeFileName(raw: String?): String {
    val last = (raw ?: "").substringAfterLast('/').substringAfterLast('\\')
    val cleaned = last.filter { it.code >= 0x20 && it.code != 0x7f }.trim().trim('.').take(120)
    return if (cleaned.isEmpty()) "file_${System.currentTimeMillis()}.wav" else cleaned
}
