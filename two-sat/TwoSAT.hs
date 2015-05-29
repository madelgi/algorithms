--------------------------------------------------------------------------------
-- |
-- Module:        TwoSAT
-- Description:   Check if a given 2SAT instance is satisfiable.
--
--------------------------------------------------------------------------------
module TwoSAT
   ( main
   ) where

import Data.Graph          ( Graph, Edge, Vertex
                           , buildG, scc )
import Data.Tree           ( Tree, flatten )
import Data.List           ( intersect )

main :: IO ()
main = do
   f <- readFile "2sat1.txt"
   let n = (read . head . lines $ f) :: Int
   print . checkTrees . scc . processFile n $ f

-- | Maps the checkTree function over a list of Tree Vertex elements,
--   and then makes sure True was returned each time
checkTrees :: [Tree Vertex] -> Bool
checkTrees ts = and (map checkTree ts)

-- | Check if a given strongly connected component contains nodes which are mutual
--   negations (e.g. 1 and -1). The instance is satisfiable iff this condition is
--   not true.
checkTree :: Tree Vertex -> Bool
checkTree t | flatten t == [0] = True
checkTree t
   | intersect ft (map negate ft) == [] = True
   | otherwise                          = False
     where ft = flatten t

-- | Turn the given text file into a graph
processFile :: Int -> String -> Graph
processFile n f = buildG (-n,n) edgeList
   where edgeList = (concatMap (\[x,y] -> [(negate x,y), (negate y, x)])
                     . map (map read) . map words . tail . lines $ f) :: [Edge]
