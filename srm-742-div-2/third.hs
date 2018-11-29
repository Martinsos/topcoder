module ResistorFactory (construct) where

import Data.List (foldl')
import Text.Printf (printf)

precisionInNanoOhm = 0.1 :: Double -- In task it is originally 1 nano ohm, but this is to be extra safe.

data ResistorBuild = Parallel Resistor Resistor | Series Resistor Resistor | OnePiece

instance Show ResistorBuild where
  show (Parallel r1 r2) = printf "Parallel #%d #%d" (getResistorId r1) (getResistorId r2)
  show (Series r1 r2) = printf "Series #%d #%d" (getResistorId r1) (getResistorId r2)
  show OnePiece = "OnePiece"


data Resistor = Resistor {
  getResistorId :: Int,
  getValueInNanoOhm :: Double,
  getBuild :: ResistorBuild
}

instance Show Resistor where
  show (Resistor id v build) = printf "#%d %g (%s)" id v (show build)

instance Eq Resistor where
  r1 == r2 = getValueInNanoOhm r1 == getValueInNanoOhm r2

instance Ord Resistor where
  r1 <= r2 = getValueInNanoOhm r1 <= getValueInNanoOhm r2

resistorToCommand :: Resistor -> (Int, Int, Int) -- Transforms resistor into format expected by Topcoder as result.
resistorToCommand (Resistor _ _ (Series r1 r2)) = (getResistorId r1, getResistorId r2, 0)
resistorToCommand (Resistor _ _ (Parallel r1 r2)) = (getResistorId r1, getResistorId r2, 1)
resistorToCommand _ = error "Can't be transformed to command!"

resistor0 = Resistor 0 (10^9) OnePiece -- This is the resistor we start with, 1 ohm.

createFromSeries :: Int -> Resistor -> Resistor -> Resistor
createFromSeries id r1 r2 = Resistor id (getValueInNanoOhm r1 + getValueInNanoOhm r2) (Series r1 r2)

createFromParallel :: Int -> Resistor -> Resistor -> Resistor
createFromParallel id r1 r2 = Resistor id (v1 * v2 / (v1 + v2)) (Series r1 r2)
  where (v1, v2) = (getValueInNanoOhm r1, getValueInNanoOhm r2)


type Inventory = [Resistor]

initialInventory :: Inventory
initialInventory = [resistor0] -- Initial resistor.
                   -: (extendInventory createFromSeries [1..30]) -- Big resistors (> 10^9 nano ohm).
                   -: ((createFromParallel 31 resistor0 resistor0):) -- First small resistor.
                   -: (extendInventory createFromParallel [32..70]) -- Other small resistors (< 10^9 nano ohm).
  where
    -- For each of given ids, it takes last resistor from inventory, creates new one with that id from it and
    -- adds it to the end of that same inventory, repeating the process.
    extendInventory create ids inv = foldl' (\i@(r:_) id -> (create id r r):i) inv ids
    a -: f = f a


construct :: Integer -> [(Int, Int, Int)]
construct target = transformResult $ construct' initialInventory (fromIntegral target)
  where transformResult = map resistorToCommand . tail . reverse

-- Given initial inventory and value of target resistor, it will return inventory in which
-- last resistor has that value (within defined precision).
construct' :: Inventory -> Double -> Inventory
construct' inv@(lastResistor:_) target = if diff < precisionInNanoOhm
                                         then inv -- We are done.
                                         else construct' (newResistor:inv) target
  where
    diff = target - (getValueInNanoOhm lastResistor)
    closestResistor = maximum $ filter (\r -> getValueInNanoOhm r <= diff) inv
    newResistor = createFromSeries (getResistorId lastResistor + 1) lastResistor closestResistor
