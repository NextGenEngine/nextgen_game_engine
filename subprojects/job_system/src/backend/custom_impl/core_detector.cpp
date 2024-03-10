#include "core_detector.h"

#include <hwloc.h>

int CoreDetector::detectCores() const {
  hwloc_topology_t topology;
  hwloc_topology_init(&topology);
  hwloc_topology_load(topology);
  int numCores = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_CORE);
  hwloc_topology_destroy(topology);
  return numCores;
}
