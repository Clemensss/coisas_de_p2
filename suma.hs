import Data.List
import System.IO 

add :: Int -> Int -> Int
add x y = x + y

mul :: Int -> Int -> Int
mul x y = x * y

generic :: (Int -> Int -> Int) -> [Int] -> Int -> Int
generic modi [] num = num
generic modi (x:xs) num = modi x (generic modi xs num)

espo :: Int -> Int -> Int
espo x 0 = 1
espo x 1 = x
espo x n = x * espo x (n-1)

tam :: [Int] -> Int -> Int
tam [] count = count
tam (x:xs) count = tam xs (count+1) 

sorted :: [Int] -> Bool
sorted [x] = True
sorted (x:xs) = 
	if x > head xs then False
	else sorted xs 

bubbleParse :: [Int] -> [Int]
bubbleParse [x] = [x] 
bubbleParse (x:xs) = 
	if (x > (head xs)) then [head xs] ++ bubbleParse ([x] ++ tail xs) 
	else [x] ++ bubbleParse xs

bubbleSort :: [Int] -> [Int]
bubbleSort arr = 
	if sorted l then l
	else bubbleSort l
	where l = bubbleParse arr

l = [1..10]
l2 = [6,2,4,8,3,5,7,10,1,33]

main = do
    
    let thing = bubbleSort l2
    print thing
