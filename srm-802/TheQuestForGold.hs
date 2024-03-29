#!/usr/bin/env stack
-- stack script --resolver lts-17.9 --package hspec

import Test.Hspec
import Data.Maybe (listToMaybe)


data CellType = Start | Treasure | Pit | Empty deriving (Eq)

explore :: [String] -> String
explore caveMap = if go [] [startCell] then "gold" else "no gold"
  where
    mapWidth = length $ head caveMap
    mapHeight = length caveMap

    startCell :: (Int, Int)
    startCell = head [(r, c) | r <- [0 .. mapHeight - 1], c <- [0 .. mapWidth - 1], cellType (r, c) == Start]

    -- TODO: I should transform caveMap to data structure that has O(1) access.
    -- TODO: I could also use Set for cellsVisited.

    go :: [(Int, Int)] -> [(Int, Int)] -> Bool
    go _ [] = False
    go cellsVisited (cell:cellsToExplore)
        | cellType cell == Treasure = True
        | isCellSlimy cell = go (cell:cellsVisited) cellsToExplore
        | otherwise = let additionalCellsToExplore = filter (not . (`elem` cellsVisited)) $ adjacentCells cell
                      in go (cell:cellsVisited) (additionalCellsToExplore ++ cellsToExplore)

    cellType (r, c) = case caveMap !! r !! c of
        'S' -> Start
        'T' -> Treasure
        'P' -> Pit
        '.' -> Empty
        _ -> error "Invalid cell representation."
    isCellSlimy = any ((== Pit) . cellType) . adjacentCells
    adjacentCells (r, c) = let isValidCell (r, c) = r >= 0 && r < mapHeight && c >= 0 && c < mapWidth
                           in filter isValidCell [(r-1, c), (r+1, c), (r, c-1), (r, c+1)]


main :: IO ()
main = hspec $ mapM_ (\tc -> it (show tc) $ runTest tc) testCases
  where
    runTest testCase = explore (fst testCase) `shouldBe` snd testCase
    testCases =
        [ (["S....", ".....", "...T.", "....."], "gold")
        , (["S....", "...P.", "..PTP", "...P."], "no gold")
        , (["S....", "..P.P", ".P.T.", "....."], "no gold")
        , (["S....", "P....", "...T.", "....."], "no gold")
        , (["S....", ".....", "PPP..", ".....", ".....", ".....", "..PPP", "..T.."], "gold")
        , ([".......", ".......", "..P.P..", "..PPP..", "..P.P..", ".......", "..S...."], "no gold")
        , ([".......", ".......", "..P.P..", "..PTP..", "..P.P..", ".......", "..S...."], "no gold")
        ]
