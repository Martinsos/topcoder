module ResistorFactory (construct) where

import Data.List (foldl', maximumBy)

initialInventory :: [(Int, Int, Int, Double)]
initialInventory = [(undefined, undefined, undefined, 10^9)] -- Initial resistor.
                   -: (extendInventory (\id v -> (id, id, 0, v * 2)) [0..28]) -- Big resistors (> 10^9 nano ohm).
                   -: ((0, 0, 1, 10^9 / 2):) -: (extendInventory (\id v -> (id, id, 1, v / 2)) [30..58]) -- Small resistors.
  where extendInventory create ids inv = foldl' (\i@((_,_,_,v):_) id -> (create id v):i) inv ids
        a -: f = f a

construct :: Integer -> [(Int, Int, Int)]
construct target = transformResult $ construct' initialInventory (fromIntegral target)
  where transformResult = map (\(id1, id2, c, v) -> (id1, id2, c)) . tail . reverse

construct' :: [(Int, Int, Int, Double)] -> Double -> [(Int, Int, Int, Double)]
construct' inv@(lastRes:_) target = if diff < 1 then inv else construct' (newRes:inv) target
  where lenInv = length inv
        diff = target - (value lastRes)
        (bestResId, bestRes) = maximumBy (\(_, r1) (_, r2) -> compare (value r1) (value r2))
          $ filter (\(_, r) -> value r <= diff) $ zip [lenInv - 1, lenInv - 2 .. 0] inv
        newRes = (lenInv - 1, bestResId, 0, value lastRes + value bestRes)
        value (_,_,_,v) = v
