set terminal png
set output 'convex_hull.png'
plot 'input.txt' using 1:2 title 'Points' with points pointtype 7, \
     'output.txt' using 1:2 title 'Convex Hull' with linespoints pointtype 5
