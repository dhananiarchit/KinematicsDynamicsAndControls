void subtract_v3( double *v1, double *v2, double *v_out );
void cross_product_v3( double *v1, double *v2, double *v_out );

void multiply_m3_v3( double r[3][3], double *v_in, double *v_out );
void multiply_transpose_m3_v3( double r[3][3], double *v_in, double *v_out );
void invert_m3( double m[3][3], double result[3][3] );

void invert_q( double *q_in, double *q_out );
double normalize_q( double *q_in, double *q_out );
void q_to_r( double *q, double r[3][3] );
void compose_q( double *q, double *p, double *result );
void q_to_rotvec( double *q, double *rotvec );
