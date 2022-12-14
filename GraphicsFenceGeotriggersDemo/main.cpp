// Copyright 2022 Esri.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#include "FenceGraphicsDemo.h"

#include "ArcGISRuntimeEnvironment.h"

#include <QCommandLineParser>
#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

void setAPIKey(const QGuiApplication& app, QString apiKey);

int main(int argc, char *argv[])
{
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);
  app.setApplicationName(QString("FenceGraphicsDemo - C++"));

  // Access to Esri location services requires an API key. This can be copied below or used as a command line argument.
  const QString apiKey = QString("");
  setAPIKey(app, apiKey);

  // Initialize the sample
  FenceGraphicsDemo::init();

  // Initialize application view
  QQmlApplicationEngine engine;
  // Add the import Path
  engine.addImportPath(QDir(QCoreApplication::applicationDirPath()).filePath("qml"));

#ifdef ARCGIS_RUNTIME_IMPORT_PATH_2
  engine.addImportPath(ARCGIS_RUNTIME_IMPORT_PATH_2);
#endif

  // Set the source
  engine.load(QUrl("qrc:/Samples/Analysis/FenceGraphicsDemo/main.qml"));

  return app.exec();
}

// Use of Esri location services, including basemaps and geocoding,
// requires authentication using either an ArcGIS identity or an API Key.
// 1. ArcGIS identity: An ArcGIS named user account that is a member of an
//    organization in ArcGIS Online or ArcGIS Enterprise.
// 2. API key: API key: a permanent key that grants access to
//    location services and premium content in your applications.
//    Visit your ArcGIS Developers Dashboard to create a new
//    API key or access an existing API key.

void setAPIKey(const QGuiApplication& app, QString apiKey)
{
  if (apiKey.isEmpty())
  {
    // Try parsing API key from command line argument, which uses the following syntax "-k <apiKey>".
    QCommandLineParser cmdParser;
    QCommandLineOption apiKeyArgument(QStringList{"k", "api"}, "The API Key property used to access Esri location services", "apiKeyInput");
    cmdParser.addOption(apiKeyArgument);
    cmdParser.process(app);

    apiKey = cmdParser.value(apiKeyArgument);

    if (apiKey.isEmpty())
    {
      qWarning() << "Use of Esri location services, including basemaps, requires" <<
                    "you to authenticate with an ArcGIS identity or set the API Key property.";
      return;
    }
  }

  Esri::ArcGISRuntime::ArcGISRuntimeEnvironment::setApiKey(apiKey);
}

