module ResistorFactory (construct) where

resistorValuePrecisionInNanoOhm = 0.1 :: Double -- In task it is originally 1 nano ohm, but this is to be extra safe.
maxResistorValueInNanoOhm = 10^18 :: Double

data Connection = Parallel | Series

data ResistorBuild = Combination Resistor Resistor Connection | OnePiece

data Resistor = Resistor {
  getResistorId :: Int,
  getValueInNanoOhm :: Double,
  getCombination :: ResistorBuild
}

resistor0 = Resistor 0 (10^9) OnePiece -- This is the resistor we start with, 1 ohm.

resistorToTuple :: Resistor -> (Int, Int, Int) -- Transforms resistor into format expected by Topcoder as result.
resistorToTuple (Resistor _ _ (Combination r1 r2 conn)) = (getResistorId r1, getResistorId r2, connToNum conn)
  where connToNum Series = 0
        connToNum Parallel = 1


construct :: Integer -> [Int]
construct targetResistor = undefined -- TODO
