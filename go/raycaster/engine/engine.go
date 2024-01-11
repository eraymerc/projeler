package engine

import (
	"math"
	"raycaster/engine/maps"
)

func Run() {
	//fmt.Println("Engine Started")
}

var LoadedMap *maps.Map

func Load(GameMap *maps.Map) {

	LoadedMap = GameMap

}

func CalculateDistanceBetweenPoints(object1 Coordinates, object2 Coordinates) float32 {

	return float32(math.Sqrt(math.Pow((float64(object1.X)-float64(object2.X)), 2) + math.Pow((float64(object1.Y)-float64(object2.Y)), 2)))

}

type Line struct {
	A Coordinates
	B Coordinates
}

type Coordinates struct {
	X float32
	Y float32
}

type Ray struct {
	Distance  float32
	Collision Coordinates
	Angle     float32
}
