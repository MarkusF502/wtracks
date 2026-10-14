import java.util.Properties

// Assinatura de release (Fase 0.1.1 do plano): a chave fica fora do repositório. Vem de android/key.properties (storeFile,
// storePassword, keyAlias, keyPassword) ou das variáveis de ambiente WTRACKS_KEYSTORE_FILE, WTRACKS_KEYSTORE_PASSWORD,
// WTRACKS_KEY_ALIAS e WTRACKS_KEY_PASSWORD (o CI as preenche a partir dos secrets). Sem chave a build cai na assinatura de DEBUG,
// que muda a cada máquina: serve para desenvolvimento, não para distribuir (WTRACKS_REQUIRE_RELEASE_SIGNING=true faz a build falhar).
val keyProperties = Properties().apply {
    val file = rootProject.file("key.properties")
    if (file.exists()) file.inputStream().use { load(it) }
}
fun signingValue(property: String, env: String): String? = System.getenv(env)?.takeIf { it.isNotBlank() } ?: keyProperties.getProperty(property)
val releaseStoreFile: File? = signingValue("storeFile", "WTRACKS_KEYSTORE_FILE")?.let { path ->
    File(path).takeIf { it.exists() } ?: rootProject.file(path).takeIf { it.exists() }
}
val hasReleaseKey = releaseStoreFile != null

plugins {
    id("com.android.application")
    // The Flutter Gradle Plugin must be applied after the Android and Kotlin Gradle plugins.
    id("dev.flutter.flutter-gradle-plugin")
}

android {
    namespace = "com.example.flutter_app"
    compileSdk = 36
    ndkVersion = flutter.ndkVersion

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }

    defaultConfig {
        // TODO: Specify your own unique Application ID (https://developer.android.com/studio/build/application-id.html).
        applicationId = "com.example.flutter_app"
        // You can update the following values to match your application needs.
        // For more information, see: https://flutter.dev/to/review-gradle-config.
        minSdk = flutter.minSdkVersion
        targetSdk = flutter.targetSdkVersion
        versionCode = flutter.versionCode
        versionName = flutter.versionName
    }

    signingConfigs {
        if (hasReleaseKey) {
            create("release") {
                storeFile = releaseStoreFile
                storePassword = signingValue("storePassword", "WTRACKS_KEYSTORE_PASSWORD")
                keyAlias = signingValue("keyAlias", "WTRACKS_KEY_ALIAS")
                keyPassword = signingValue("keyPassword", "WTRACKS_KEY_PASSWORD")
            }
        }
    }

    buildTypes {
        release {
            if (hasReleaseKey) {
                signingConfig = signingConfigs.getByName("release")
            } else {
                if (System.getenv("WTRACKS_REQUIRE_RELEASE_SIGNING") == "true") {
                    throw GradleException("Chave de assinatura de release não encontrada (key.properties ou WTRACKS_KEYSTORE_*).")
                }
                logger.warn("WTracks: sem chave de release; assinando com a chave de DEBUG (não distribua este APK).")
                signingConfig = signingConfigs.getByName("debug")
            }
        }
    }

    externalNativeBuild {
        cmake {
            path = file("../../../native/CMakeLists.txt")
        }
    }
}

kotlin {
    compilerOptions {
        jvmTarget = org.jetbrains.kotlin.gradle.dsl.JvmTarget.JVM_17
    }
}

flutter {
    source = "../.."
}
