// example_1.sce part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech
// units are in meters.
camera {
  at (0 1.3 -12)
  look-at (0 1 0)
  down (0 -1 0)
  width 36.
  height 24.
  depth 50.
  resolution (1024 683)
  illumination beam
}

object {
  sphere {
    radius 1.0
    center (-0.8. 1. 1.)
  }
  
  material {
    diffuse colour (1 0 0)
  }
}

object {
  sphere {
    radius 1.0
    center (0. 1. 1.)
  }
  
  material {
    diffuse colour (0 1 0)
  }
}

object {
  sphere {
    radius 1.0
    center (0.8 1 1)
  }
  
  material {
    diffuse colour (1 0 1)
  }
}

object {
  plane {
    position (0. 0. 0)
    normal (0. 1. 0.)
  }
  
  material {
    diffuse colour (0.5, 0.5, 0.5)
  }
}
