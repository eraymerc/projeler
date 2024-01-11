package engine

import "math"

const CELLSIZE int = 55

var SCREEN_WIDTH = []int{1200, 650}

const RAYCOUNT int = 240

const DEPTH int = 10 * int(CELLSIZE)

const FOV float32 = 66 //in degrees (66 is recommended)
var FOCAL_DIST float32 = (float32(SCREEN_WIDTH[0]) / 2) / float32(math.Tan(float64((3.1415926/180)*(FOV/2))))
