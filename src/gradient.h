/*
Bina BADIANE
11928259
*/

/* function which returns a pointer to the maximum and the minimum in the
interval [borne_inf1, borne_sup1] x [borne_inf2, borne_sup2] */
uint8_t *bounds(Im img, int32_t borne_inf1, int32_t borne_sup1, int32_t borne_inf2, int32_t borne_sup2);
// function which calculates the gradient of the image img with a radius r
Im *calculateGradient(Im img, int32_t r);
