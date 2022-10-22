/* calculate the exact distance between two points: (x0,y0) and (x1, y1) */
double dist(double x0, double y0, double x1, double y1);

/* create a side_length x side_length image with each pixce colored to
 * (0, 0, b) where b is the sin of the distance between the pixel and the 
 * offset center, scaled linearly to an integer value between 0 and 255 */
void draw_waves(int side_length, int x_offset, int y_offset);
