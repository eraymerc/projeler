package main

import (
	"image/color"
	"io/ioutil"
	"log"
	"math"
	"raycaster/engine"
	"raycaster/engine/maps"
	"strconv"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/inpututil"
	"github.com/hajimehoshi/ebiten/v2/text"
	"github.com/hajimehoshi/ebiten/v2/vector"
	"golang.org/x/image/font"
	"golang.org/x/image/font/opentype"
)

type Game struct {
	keys []ebiten.Key
}

var player engine.Player

var (
	mplusNormalFont font.Face
	mplusBigFont    font.Face
	//jaKanjis        = []rune{}
)

func (g *Game) Update() error {
	//R.ApplyForce(&engine.Vector2D{2, 2}, 1/60)
	g.keys = inpututil.AppendPressedKeys(g.keys[:0])

	for i := 0; i < len(g.keys); i++ {

		if g.keys[i] == ebiten.KeyW {
			player.Move(0)
		}
		if g.keys[i] == ebiten.KeyA {
			player.Move(3)
		}
		if g.keys[i] == ebiten.KeyS {
			player.Move(1)
		}
		if g.keys[i] == ebiten.KeyD {
			player.Move(2)
		}
		if g.keys[i] == ebiten.KeyRight {
			player.Rotate(1)
		}
		if g.keys[i] == ebiten.KeyLeft {
			player.Rotate(-1)
		}
		if g.keys[i] == ebiten.KeyR {
			player.Move(4)
		}
	}

	player.CheckRays(engine.LoadedMap)

	return nil
}

func (g *Game) Draw(screen *ebiten.Image) {

	vector.DrawFilledRect(screen, 0, 0, float32(engine.SCREEN_WIDTH[0]), float32(engine.SCREEN_WIDTH[1])/2, color.RGBA{18, 99, 255, 255}, true)
	vector.DrawFilledRect(screen, 0, float32(engine.SCREEN_WIDTH[1])/2, float32(engine.SCREEN_WIDTH[0]), float32(engine.SCREEN_WIDTH[1])/2, color.White, true)
	vector.DrawFilledRect(screen, 0, float32(engine.SCREEN_WIDTH[1])/2, float32(engine.SCREEN_WIDTH[0]), float32(engine.SCREEN_WIDTH[1])/2, color.RGBA{0, 0, 0, 220}, true)

	//vector.StrokeLine(screen, x1, y1, x2, y2, 10, color.RGBA{0xff, 0, 0, 0xff}, true)
	//vector.DrawFilledCircle(screen, player.Location.X, player.Location.Y, player.Width*float32(engine.CELLSIZE), color.White, true)

	//cosine := float32(math.Cos(float64((3.1415926 / 180) * player.Direction)))
	//sine := float32(math.Sin(float64((3.1415926 / 180) * player.Direction)))

	//vector.StrokeLine(screen, player.Location.X, player.Location.Y, player.Location.X+player.Width*float32(engine.CELLSIZE)*cosine, player.Location.Y+player.Width*float32(engine.CELLSIZE)*sine, player.Width*0.2*float32(engine.CELLSIZE), color.Black, true)
	//vector.DrawFilledCircle(screen, R.Location.X, R.Location.Y, 3, color.RGBA{0xff, 0, 0, 0xff}, true)

	//LOAD 3D ;)
	for i := 0; i < engine.RAYCOUNT; i++ {
		raywidth := engine.SCREEN_WIDTH[0] / engine.RAYCOUNT
		dist := player.Rays[i].Distance
		rayheight := engine.FOCAL_DIST * float32(engine.CELLSIZE) / dist
		//(float32(engine.SCREEN_WIDTH[1]) / engine.FOCAL_DIST) * dist

		if dist != 0 {
			vector.DrawFilledRect(screen, float32(i*raywidth), float32((engine.SCREEN_WIDTH[1]-int(rayheight))/2), float32(raywidth), float32(rayheight), color.RGBA{18, 99, 34, 255}, true)
			alpha := uint8(math.Floor(float64((dist / float32(engine.DEPTH)) * 255)))
			vector.DrawFilledRect(screen, float32(i*raywidth), float32((engine.SCREEN_WIDTH[1]-int(rayheight))/2), float32(raywidth), float32(rayheight), color.RGBA{18, 99, 34, alpha}, true)
		}
	}

	//LOAD RAYS
	for i := 0; i < engine.RAYCOUNT; i++ {

		vector.StrokeLine(screen, player.Location.X, player.Location.Y, player.Rays[i].Collision.X, player.Rays[i].Collision.Y, 2, color.RGBA{0xff, 0, 0, 0xff}, true)

	}

	//load map
	for i := 0; i < len(maps.MAP_1.Data); i++ {
		for j := 0; j < len(maps.MAP_1.Data[i]); j++ {
			if maps.MAP_1.Data[i][j] == 1 {
				vector.DrawFilledRect(screen, float32(j*engine.CELLSIZE), float32(i*engine.CELLSIZE), float32(engine.CELLSIZE), float32(engine.CELLSIZE), color.White, true)
			}
		}
	}

	text.Draw(screen, "FPS : "+strconv.Itoa(int(ebiten.ActualFPS())), mplusNormalFont, 10, 24, color.White)
	text.Draw(screen, "TPS : "+strconv.Itoa(int(ebiten.ActualTPS())), mplusNormalFont, 10, 48, color.White)
}

func (g *Game) Layout(outsideWidth, outsideHeight int) (screenWidth, screenHeight int) {
	return engine.SCREEN_WIDTH[0], engine.SCREEN_WIDTH[1]
}

func init() {

	pixeloidsans, err := ioutil.ReadFile("PixeloidSans.ttf")

	if err != nil {
		log.Fatal(err)
	}

	tt, err := opentype.Parse(pixeloidsans)
	if err != nil {
		log.Fatal(err)
	}

	const dpi = 72
	mplusNormalFont, err = opentype.NewFace(tt, &opentype.FaceOptions{
		Size:    27, //9'un katlari olmasi idealdir
		DPI:     dpi,
		Hinting: font.HintingVertical,
	})
	if err != nil {
		log.Fatal(err)
	}
	mplusBigFont, err = opentype.NewFace(tt, &opentype.FaceOptions{
		Size:    48,
		DPI:     dpi,
		Hinting: font.HintingFull, // Use quantization to save glyph cache images.
	})
	if err != nil {
		log.Fatal(err)
	}

	// Adjust the line height.
	mplusBigFont = text.FaceWithLineHeight(mplusBigFont, 54)

	//load engine
	engine.Load(&maps.MAP_1)
}

func main() {

	//arrayOfObjects = append(arrayOfObjects, &R)
	//arrayOfObjects = append(arrayOfObjects, &Earth)
	player.Direction = -90
	player.Location.X = 150
	player.Location.Y = 150
	player.Speed = 3
	player.RotateSpeed = 5
	player.Width = 0.3
	player.CreateRays()

	ebiten.SetWindowSize(engine.SCREEN_WIDTH[0], engine.SCREEN_WIDTH[1])
	ebiten.SetWindowTitle("raycaster")
	if err := ebiten.RunGame(&Game{}); err != nil {
		log.Fatal(err)
	}
}
