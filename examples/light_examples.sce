// example_1.sce part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech
// units are in meters.
camera {
  at (100 10 1)
  look-at (0 0 0)
  down (0. -1. 0.)
  width 36.
  height 24.
  depth 50.
  resolution (1024 549)
}

light {
  point {
    position (0. 10. 0.)
  }
  colour (1. 1. 1.)
}

light {
  sky {
    pole (0 1 0)
    polar colour (0 0 0.5)
  }
  colour (0.4 0.4 1.0)
}

light {
  directional {
    from (0 -1 0)
  }
  colour (1 1 1)
}
object {
  sphere {
    radius 1.0
    center (0. 1. 0.)
  }
  
  material {
    diffuse colour (1. 0. 0.)
  }
}

object {
  plane {
    position (0. 0. 0.)
    normal (0. 1. 0.)
  }
  
  material {
    diffuse colour (200 10 9)
  }
}

