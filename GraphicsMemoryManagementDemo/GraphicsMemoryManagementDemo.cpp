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

#ifdef PCH_BUILD
#include "pch.hpp"
#endif // PCH_BUILD

#include "GraphicsMemoryManagementDemo.h"

#include "Basemap.h"
#include "Map.h"
#include "MapQuickView.h"
#include "Graphic.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleRenderer.h"

// display current RAM
#include<mach/mach.h>

#include <QUrl>

using namespace Esri::ArcGISRuntime;

GraphicsMemoryManagementDemo::GraphicsMemoryManagementDemo(QObject* parent /* = nullptr */):
  QObject(parent),
  m_map(new Map(BasemapStyle::ArcGISTerrain, this))
{
  m_graphicsOverlay = new GraphicsOverlay(this);

  SimpleRenderer* pointRenderer = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle,Qt::blue, 5, this), this);
  m_graphicsOverlay->setRenderer(pointRenderer);

  m_graphicsParent.reset(new QObject); // why?????
}

GraphicsMemoryManagementDemo::~GraphicsMemoryManagementDemo()
{
}

void GraphicsMemoryManagementDemo::init()
{
  // Register the map view for QML
  qmlRegisterType<MapQuickView>("Esri.Samples", 1, 0, "MapView");
  qmlRegisterType<GraphicsMemoryManagementDemo>("Esri.Samples", 1, 0, "GraphicsMemoryManagementDemoSample");
}

MapQuickView* GraphicsMemoryManagementDemo::mapView() const
{
  return m_mapView;
}

// Set the view (created in QML)
void GraphicsMemoryManagementDemo::setMapView(MapQuickView* mapView)
{
  if (!mapView || mapView == m_mapView)
  {
    return;
  }

  m_mapView = mapView;
  m_mapView->setMap(m_map);

  m_mapView->graphicsOverlays()->append(m_graphicsOverlay);

  emit mapViewChanged();
  memoryUsage();

  connect(m_mapView, &MapQuickView::drawStatusChanged, this, [this]()
  {
    memoryUsage();
  });
}

void GraphicsMemoryManagementDemo::badMemoryManagement()
{
  for (int i = 0; i < 100'000; ++i)
  {
    m_graphicsOverlay->graphics()->append(new Graphic(Point(rand()*40,rand()*40), this));
  }
  emit graphicsOverlayCountChanged();
}

void GraphicsMemoryManagementDemo::properMemoryManagement()
{
  for (int i = 0; i < 100'000; ++i)
  {
    m_graphicsOverlay->graphics()->append(new Graphic(Point(rand()*40,rand()*40), m_graphicsParent.get()));
  }
  emit graphicsOverlayCountChanged();
}

void GraphicsMemoryManagementDemo::clearGraphics()
{
  m_graphicsOverlay->graphics()->clear();
  m_graphicsParent.reset(new QObject);
  emit graphicsOverlayCountChanged();
}

int GraphicsMemoryManagementDemo::graphicsOverlayCount() const
{
  return m_graphicsOverlay->graphics()->size();
}




// Displays the current resident memory useage of the application

void GraphicsMemoryManagementDemo::memoryUsage()
{
  struct task_basic_info t_info;
  mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
  if (KERN_SUCCESS == task_info(mach_task_self(),
                                TASK_BASIC_INFO, (task_info_t)&t_info,
                                &t_info_count))
  {
    setUsedMemory(t_info.resident_size/1e9);
    emit memoryUsageChanged();
  }
}

double GraphicsMemoryManagementDemo::usedMemory() const
{
  return m_usedMemory;
}

void GraphicsMemoryManagementDemo::setUsedMemory(double usedMemory)
{
  m_usedMemory = usedMemory;
}
