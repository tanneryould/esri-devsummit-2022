// [WriteFile Name=GraphicsMemoryManagementDemo, Category=Analysis]
// [Legal]
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
// [Legal]

#ifndef GRAPHICSMEMORYMANAGEMENTDEMO_H
#define GRAPHICSMEMORYMANAGEMENTDEMO_H

namespace Esri
{
namespace ArcGISRuntime
{
class GraphicsOverlay;
class Map;
class MapQuickView;
}
}

#include <QObject>

class GraphicsMemoryManagementDemo : public QObject
{
  Q_OBJECT

  Q_PROPERTY(Esri::ArcGISRuntime::MapQuickView* mapView READ mapView WRITE setMapView NOTIFY mapViewChanged)
  Q_PROPERTY(int graphicsOverlayCount READ graphicsOverlayCount NOTIFY graphicsOverlayCountChanged)
  Q_PROPERTY(double usedMemory READ usedMemory WRITE setUsedMemory NOTIFY memoryUsageChanged)

public:
  explicit GraphicsMemoryManagementDemo(QObject* parent = nullptr);
  ~GraphicsMemoryManagementDemo() override;

  static void init();

  Q_INVOKABLE void badMemoryManagement();
  Q_INVOKABLE void properMemoryManagement();
  Q_INVOKABLE void clearGraphics();

signals:
  void mapViewChanged();
  void memoryUsageChanged();
  void graphicsOverlayCountChanged();

private:
  Esri::ArcGISRuntime::MapQuickView* mapView() const;
  void setMapView(Esri::ArcGISRuntime::MapQuickView* mapView);

  int graphicsOverlayCount() const;

  double usedMemory() const;
  void setUsedMemory(double usedMemory);

  void memoryUsage();

  Esri::ArcGISRuntime::Map* m_map = nullptr;
  Esri::ArcGISRuntime::MapQuickView* m_mapView = nullptr;

  Esri::ArcGISRuntime::GraphicsOverlay* m_graphicsOverlay = nullptr;

  QScopedPointer<QObject> m_graphicsParent;

  double m_usedMemory;
};

#endif // GRAPHICSMEMORYMANAGEMENTDEMO_H
