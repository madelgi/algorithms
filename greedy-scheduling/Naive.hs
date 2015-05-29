--------------------------------------------------------------------------------
-- A naive implementation of a greedy scheduling algorithm. Naive, in that
-- I don't use a hash table to speed things up.
--
--------------------------------------------------------------------------------
import Data.List ( sortBy )

main :: IO ()
main = do
   file <- readFile "test.txt"
   print . computeWeightedSum 0 . reverse .
      sortBy sortFunc . map prependDif . processText $ file

computeWeightedSum :: Int -> [[Int]] -> Int
computeWeightedSum n [] = 0
computeWeightedSum n (x:xs) = prod + rest
   where prod  = (head $ tail x) * (n + (last x))
         rest  = computeWeightedSum (n + (last x)) xs

-- Sort by first list element. If equal, sort by 2nd list element
sortFunc :: [Int] -> [Int] -> Ordering
sortFunc (x1:y1:z1) (x2:y2:z2)
   | x1 > x2   = GT
   | x1 == x2  = compare y1 y2
   | otherwise = LT

-- Calculate the difference
prependDif :: [Int] -> [Int]
prependDif [x,y] = [x-y,x,y]
prependDif xs    = xs

-- Process the textfile
processText str = let xs = map words (lines str)
                  in  map (map read) (tail xs) :: [[Int]]
