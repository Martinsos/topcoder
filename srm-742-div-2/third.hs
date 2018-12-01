module ResistorFactory (construct) where

import Data.List (foldl', maximumBy)

precisionInNanoOhm = 1 :: Double

data ResistorBuild = Parallel Resistor Resistor | Series Resistor Resistor | OnePiece
data Resistor = Resistor { getResistorId :: Int, getValueInNanoOhm :: Double, getBuild :: ResistorBuild }

resistorToCommand :: Resistor -> (Int, Int, Int) -- Transforms resistor into format expected by Topcoder as result.
resistorToCommand (Resistor _ _ (Series r1 r2)) = (getResistorId r1, getResistorId r2, 0)
resistorToCommand (Resistor _ _ (Parallel r1 r2)) = (getResistorId r1, getResistorId r2, 1)
resistorToCommand _ = error "Can't be transformed to command!"

createFromSeries :: Int -> Resistor -> Resistor -> Resistor
createFromSeries id r1 r2 = Resistor id (getValueInNanoOhm r1 + getValueInNanoOhm r2) (Series r1 r2)

createFromParallel :: Int -> Resistor -> Resistor -> Resistor
createFromParallel id r1 r2 = Resistor id (v1 * v2 / (v1 + v2)) (Parallel r1 r2)
  where (v1, v2) = (getValueInNanoOhm r1, getValueInNanoOhm r2)

type Inventory = [Resistor]

resistor0 = Resistor 0 (10^9) OnePiece -- This is the resistor we start with, 1 ohm.

initialInventory :: Inventory
initialInventory = [resistor0] -- Initial resistor.
                   -: (extendInventory createFromSeries [1..29]) -- Big resistors (> 10^9 nano ohm).
                   -: ((createFromParallel 30 resistor0 resistor0):) -- First small resistor.
                   -: (extendInventory createFromParallel [31..59]) -- Other small resistors (< 10^9 nano ohm).
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
    closestResistor = maximumBy (\r1 r2 -> compare (getValueInNanoOhm r1) (getValueInNanoOhm r2))
      $ filter (\r -> getValueInNanoOhm r <= diff) inv
    newResistor = createFromSeries (getResistorId lastResistor + 1) lastResistor closestResistor
