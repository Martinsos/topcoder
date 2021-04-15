module TheQuestForGold
    (
    ) where

import Data.Maybe (listToMaybe)
import Data.List (partition)


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


test :: IO Bool
test = do
    -- NOTE: This block shouldn't change from problem to problem.
    let executedTests = map (\t -> (runTestCase explore t, t)) testCases
    let (passedTests, failedTests) = partition (fst . fst) executedTests
    putStrLn "((<passed>, (<result>, <expected>)), <test_case>)"
    putStrLn "Passed tests:"
    mapM_ (putStrLn . show) passedTests
    putStrLn "Failed tests:"
    mapM_ (putStrLn . show) failedTests
    if null failedTests
        then putStrLn "SUCCESS: All tests passed!" >> return True
        else putStrLn "FAILURE: Some tests failed." >> return False
  where
    -- NOTE: Logic below is specific per problem.
    runTestCase f testCase = let result = f $ fst testCase
                                 expected = snd testCase
                                 passed = result == expected
                             in (passed, (result, expected))
    testCases =
        [ (["S....", ".....", "...T.", "....."], "gold")
        , (["S....", "...P.", "..PTP", "...P."], "no gold")
        , (["S....", "..P.P", ".P.T.", "....."], "no gold")
        , (["S....", "P....", "...T.", "....."], "no gold")
        , (["S....", ".....", "PPP..", ".....", ".....", ".....", "..PPP", "..T.."], "gold")
        , ([".......", ".......", "..P.P..", "..PPP..", "..P.P..", ".......", "..S...."], "no gold")
        , ([".......", ".......", "..P.P..", "..PTP..", "..P.P..", ".......", "..S...."], "no gold")
        ]
