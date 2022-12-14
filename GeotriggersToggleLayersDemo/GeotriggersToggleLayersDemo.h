// [WriteFile Name=GeotriggersToggleLayersDemo, Category=Analysis]
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

#ifndef GEOTRIGGERSTOGGLELAYERSDEMO_H
#define GEOTRIGGERSTOGGLELAYERSDEMO_H

namespace Esri
{
namespace ArcGISRuntime
{
class Map;
class MapQuickView;
class SimulatedLocationDataSource;
class LocationGeotriggerFeed;
class FeatureLayer;
class GroupLayer;
class FeatureTable;
}
}

#include <QObject>

class GeotriggersToggleLayersDemo : public QObject
{
  Q_OBJECT

  Q_PROPERTY(Esri::ArcGISRuntime::MapQuickView* mapView READ mapView WRITE setMapView NOTIFY mapViewChanged)

public:
  explicit GeotriggersToggleLayersDemo(QObject* parent = nullptr);
  ~GeotriggersToggleLayersDemo();

  static void init();

signals:
  void mapViewChanged();

private:
  Esri::ArcGISRuntime::MapQuickView* mapView() const;
  void setMapView(Esri::ArcGISRuntime::MapQuickView* mapView);

  void loadMmpk();
  void initializeSimulatedLocationDisplay();
  void runGeotriggers();

  Esri::ArcGISRuntime::Map* m_map = nullptr;
  Esri::ArcGISRuntime::MapQuickView* m_mapView = nullptr;
  Esri::ArcGISRuntime::SimulatedLocationDataSource* m_locationDataSource = nullptr;

  Esri::ArcGISRuntime::LocationGeotriggerFeed* m_geotriggerFeed = nullptr;
  Esri::ArcGISRuntime::GroupLayer* m_indoorLayers = nullptr;
  Esri::ArcGISRuntime::FeatureTable* m_buildingFootprintTable = nullptr;
};

#endif // GEOTRIGGERSTOGGLELAYERSDEMO_H
