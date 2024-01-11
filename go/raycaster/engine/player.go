package engine

import (
	"fmt"
	"math"
	"raycaster/engine/maps"
)

type Player struct {
	Location    Coordinates
	Direction   float32 //angle in degrees
	Speed       float32
	RotateSpeed float32 //in degrees
	Width       float32 // 1 = a cell
	Rays        []Ray   //rays
}

func (player *Player) CreateRays() {
	anglebetweenrays := FOV / float32(RAYCOUNT)
	rayangle := FOV / (-2)
	//angle:= (float32(RAYCOUNT))/(-2)
	for i := 0; i < RAYCOUNT; i++ {
		ray := Ray{Angle: rayangle + anglebetweenrays*float32(i)}
		player.Rays = append(player.Rays, ray)

	}

}

func (player *Player) CheckRays(MAP *maps.Map) {
	for i := 0; i < RAYCOUNT; i++ {
		//mx+b = line values
		angle := player.Direction + player.Rays[i].Angle

		xp := player.Location.X
		yp := player.Location.Y

		cos := float32(math.Cos(float64((3.1415926 / 180) * (angle))))
		sin := float32(math.Sin(float64((3.1415926 / 180) * (angle))))

		for d := 0; d < DEPTH; d++ {
			xe := math.Floor(float64((xp + float32(d)*cos) / float32(CELLSIZE)))
			ye := math.Floor(float64((yp + float32(d)*sin) / float32(CELLSIZE)))

			x := int(xe)
			y := int(ye)

			if y > len(MAP.Data)-1 || y < 0 {
				break
			} else if x > len(MAP.Data[y])-1 || x < 0 {
				break
			}
			player.Rays[i].Collision.X = player.Location.X
			player.Rays[i].Collision.Y = player.Location.Y
			if MAP.Data[y][x] != 0 {
				player.Rays[i].Collision.X = xp + float32(d)*cos
				player.Rays[i].Collision.Y = yp + float32(d)*sin
				break
			}

		}
		player.Rays[i].Distance = CalculateDistanceBetweenPoints(player.Location, player.Rays[i].Collision)

	}
}

/*
func (player *Player) CalculateRayDistances() {
	for i := 0; i < RAYCOUNT; i++ {
		player.Rays[i].Distance = CalculateDistanceBetweenPoints(player.Location, player.Rays[i].Collision)
	}
}*/

func (player *Player) Rotate(rotation float32) {
	player.Direction += rotation * player.RotateSpeed
	if player.Direction > 360 {
		player.Direction -= 360
	} else if player.Direction < 360 {
		player.Direction += 360

	}
}

func (player *Player) Move(x int) {
	pcos := float32(math.Cos(float64((3.1415926 / 180) * player.Direction)))
	psin := float32(math.Sin(float64((3.1415926 / 180) * player.Direction)))

	// yukari = 0
	// asagi = 1
	//saga = 2
	//sola = 3
	//konumu sifirka = 4

	switch x {
	case 0:
		player.Location.X += player.Speed * pcos
		player.Location.Y += player.Speed * psin

	case 1:
		player.Location.X -= player.Speed * pcos
		player.Location.Y -= player.Speed * psin
	case 2:
		player.Location.X -= player.Speed * psin
		player.Location.Y += player.Speed * pcos
	case 3:
		player.Location.X += player.Speed * psin
		player.Location.Y -= player.Speed * pcos
	case 4:
		player.Location.X = 200
		player.Location.Y = 200
	default:
		fmt.Println("tanimlanmamis sayi")
	}

	//fmt.Println(player.Location)

}
