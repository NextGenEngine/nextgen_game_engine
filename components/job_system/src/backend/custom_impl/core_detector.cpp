#include "core_detector.h"

#include <hwloc.h>

int CoreDetector::detectCores() {
  hwloc_topology_t topology = nullptr;
  hwloc_topology_init(&topology);
  hwloc_topology_load(topology);
  int const numCores = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_CORE);
  hwloc_topology_destroy(topology);
  return numCores;
}
