#ifndef __KALMAN_FILTER_H__
#define __KALMAN_FILTER_H__

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Legend:
 *   xhat_k_km1    --   Predicted state at time 'k'   using information available at time 'k-1'
 *      P_k_km1    --   Predicted covariance at time 'k' using information available at time 'k-1'
 *      F_k        --   State transition model
 *      u_k        --   Control vector (i.e. external process)
 *      B_k        --   Control input model
 *      w_k        --   Gaussian White noise
 *      H_k        --   Observation model (to transform true state into measurements)
 *      Q_k        --   Covariance matrix of process noise
 *      R_k        --   Covariance of observational noise
 *      v_k        --   Gaussian white observational noise
 *
 * PREDICTION PHASE
 *   Predicted state:        xhat_k_km1 = Fk * xhat_km1_km1    +  Bk * uk
 *   Predicted covar:           P_k_km1 = Fk * P_km1_km1 * Fk' +  Qk
 *
 * UPDATE PHASE
 *   Measurement residual:       yhat_k = zk - Hk * xhat_k_km1
 *   Residual covariance:           S_k = H_k * P_k_km1 * H_k' + R_k
 *   Optimal Kalman gain:           K_k = P_k_km1 * H_k' * inv(S_k)
 *   Updated state esti:       xhat_k_k = xhat_k_km1 + K_k * yhat_k
 *   Updated covariance:          P_k_k = (I - K_k * H_k) * P_k_km1
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define KAL_STRIDE 36
#define KAL_MAT(_var)  float _var[KAL_STRIDE][KAL_STRIDE]
#define KAL_VEC(_var)  float _var[KAL_STRIDE]

void KalmanPredict(
    KAL_VEC(xhat_k_km1),    /* OUTPUT: (S)     Predicted state at time 'k' */
    KAL_MAT(P_k_km1),       /* OUTPUT: (S x S) Predicted covariance at time 'k' */
    KAL_MAT(P_km1_km1),     /* INPUT:  (S x S) Updated covariance from time 'k-1' */
    KAL_VEC(xhat_km1_km1),  /* INPUT:  (S)     Updated state from time 'k-1' */
    KAL_MAT(F_k),           /* INPUT:  (S x S) State transition model */
    KAL_MAT(B_k),           /* INPUT:  (S x U) Control input model */
    KAL_VEC(u_k),           /* INPUT:  (U)     Control vector */
    KAL_MAT(Q_k),           /* INPUT:  (S x S) Covariance of process noise */
    int S,                  /* INPUT:          Number of dimensions in state vector */
    int U);                 /* INPUT:          Size of control input vector */

void KalmanUpdate(
    KAL_VEC(xhat_k_k),      /* OUTPUT: Updated state at time 'k' */
    KAL_MAT(P_k_k),         /* OUTPUT: Updated covariance at time 'k' */
    KAL_VEC(xhat_k_km1),    /* INPUT:  Predicted state at time 'k' */
    KAL_MAT(P_k_km1),       /* INPUT:  Predicted covariance at time 'k' */
    KAL_MAT(H_k),           /* INPUT:  Observational model */
    KAL_MAT(R_k),           /* INPUT:  Covariance of observational noise */
    int B,                  /* INPUT:  Number of observations in observation vector */
    int S);                 /* INPUT:  Number of measurements in the state vector */

/* * * * * * * * * * * *
 * State vector format:
 *  xhat[12] = { x, y, z, ix, iy, iz, jx, jy, jz, kx, ky, kz, vx, vy, vz, vix, viy, viz, vjx, vjy, vjz, vkx, vky, vkz, ax, ay, az, aix, aiy, aiz, ajx, ajy, ajz, akx, aky, akz },
 *               0  1  2   3   4   5   6   7   8   9  10  11  12  13  14   15   16   17   18   19   20   21   22   23  24  25  26   27   28   29   30   31   32   33   34   35
 *  where,
 *    i  --  right direction vector
 *    j  --  forward direction vector
 *    k  --  up direction vector
 * * * * * * * * * * * */

/* positional state */
#define ST_X   0
#define ST_Y   1
#define ST_Z   2
#define ST_IX  3
#define ST_IY  4
#define ST_IZ  5
#define ST_JX  6
#define ST_JY  7
#define ST_JZ  8
#define ST_KX  9
#define ST_KY 10
#define ST_KZ 11

/* velocity state */
#define ST_VX   0
#define ST_VY   1
#define ST_VZ   2
#define ST_VIX  3
#define ST_VIY  4
#define ST_VIZ  5
#define ST_VJX  6
#define ST_VJY  7
#define ST_VJZ  8
#define ST_VKX  9
#define ST_VKY 10
#define ST_VKZ 11

/* acceleration state */
#define ST_AX   0
#define ST_AY   1
#define ST_AZ   2
#define ST_AIX  3
#define ST_AIY  4
#define ST_AIZ  5
#define ST_AJX  6
#define ST_AJY  7
#define ST_AJZ  8
#define ST_AKX  9
#define ST_AKY 10
#define ST_AKZ 11


/* * * * * * * * * * * *
 * Measurement:
 * * * * * * * * * * * */

#endif

