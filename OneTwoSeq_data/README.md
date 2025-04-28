This folder contains the following data:

* `sobolOneTwoSeq_init_tab.dat` -- initialization data for 692 dimensions, in Joe and Kuo format
* `matrices_sobolOneTwoSeq.dat` -- generator matrices for 692 dimensions, of size 32x32
* `complementary_init_tab_JoeKuo_without_OneTwoSeq.dat` -- complementary initialization data from new-joe-kuo-6.21201, not conflicting with the entries of sobolOneTwoSeq_init_tab.dat
* `matrices_Ke/` -- directory, that contains matrices Ke (see Algorithm 1)
    - Ke_e1_2.dat       2 matrices of size of 2e x e2 = 2 x 2
    - Ke_e2_6.dat       6 matrices of size of 2e x e2 = 4 x 4
    - Ke_e3_40.dat      40 matrices of size of 2e x e2 = 6 x 6
    - Ke_e4_1688.dat    1688 matrices of size of 2e x e2 = 8 x 8
    - Ke_e5_727.dat     727 matrices of size of 2e x e2 = 10 x 10

Joe and Kuo format is described on the following page: https://web.maths.unsw.edu.au/~fkuo/sobol/
and also in
https://web.maths.unsw.edu.au/~fkuo/sobol/joe-kuo-notes.pdf
and
`S. Joe and F. Y. Kuo (2008), Constructing Sobol′ sequences with better two-dimensional
projections, SIAM J. Sci. Comput. 30, 2635–2654`

*Attention:* our file sobolOneTwoSeq_init_tab.dat contains the following entry
0 0 0 # this is a pseudo-entry, which corresponds to van-der-Corput (identity generator matrix)

Joe and Kuo format treats the first van-der-Corput entry as an exception!
The file new-joe-kuo-6.21201 on their site does not contain this entry.
