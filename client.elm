module Client where

import Graphics.Element exposing (Element)
import Graphics.Collage exposing (..)
import Task exposing (Task, andThen)
import SocketIO
import Array exposing (Array)
import Color exposing (black, green)
import Json.Decode exposing (Decoder, tuple2, int, float, decodeString)

main : Signal Element
main = Signal.map view (Signal.foldp update init validSocketData)

-- MODEL

type alias Model = Array (Float,Float)

init : Model
init = Array.initialize 150 (always (200,0))

-- SIGNALS

socket : Task x SocketIO.Socket
socket = SocketIO.io "http://localhost:8050" SocketIO.defaultOptions

received : Signal.Mailbox String
received = Signal.mailbox "200"

port responses : Task x ()
port responses = socket `andThen` SocketIO.on "data" received.address

decoder : Decoder (Int,Float)
decoder =
  tuple2 (,) int float

validSocketData : Signal (Int,Float)
validSocketData =
  Signal.filterMap ((decodeString decoder)>>Result.toMaybe) (0,0) received.signal

-- HELPERS

cartesionPoint : Float -> Float -> (Float,Float)
cartesionPoint angle radius =
  let
    x = radius * (cos (degrees angle))
    y = radius * (sin (degrees angle))
  in
    (x,y)

-- UPDATE

update : (Int,Float) -> Model -> Model
update (angle,distance) model =
  Array.map (\(d,opacity) -> (d,opacity-0.0035)) model
    |> Array.set angle (distance,0.6)

-- VIEW

view : Model -> Element
view model =
  let
    segments = Array.toList (Array.indexedMap (\index (distance,opacity) -> point (toFloat index) distance opacity) model)
  in
    collage 500 500 <| 
      (circle 200 |> filled black) ::
      (circle 200 |> outlined { defaultLine | color <- green }) ::
      (circle 150 |> outlined { defaultLine | color <- green }) ::
      (circle 100 |> outlined { defaultLine | color <- green }) ::
      (circle 50  |> outlined { defaultLine | color <- green }) ::
      segments
    

point : Float -> Float -> Float -> Form
point angle distance opacity =
  circle 5
    |> filled (Color.rgba 0 220 0 opacity)
    |> move (cartesionPoint angle distance)
