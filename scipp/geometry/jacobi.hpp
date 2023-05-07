/**
 * @file    geometry/matrix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-25
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::geometry {

procedure jacobi(S ∈ Rn×n; out e ∈ Rn; out E ∈ Rn×n)
  var
    i, k, l, m, state ∈ N
    s, c, t, p, y, d, r ∈ R
    ind ∈ Nn
    changed ∈ Ln

  function maxind(k ∈ N) ∈ N ! index of largest off-diagonal element in row k
    m := k+1
    for i := k+2 to n do
      if │Ski│ > │Skm│ then m := i endif
    endfor
    return m
  endfunc

  procedure update(k ∈ N; t ∈ R) ! update ek and its status
    y := ek; ek := y+t
    if changedk and (y=ek) then changedk := false; state := state−1
    elsif (not changedk) and (y≠ek) then changedk := true; state := state+1
    endif
  endproc

  procedure rotate(k,l,i,j ∈ N) ! perform rotation of Sij, Skl
    ┌   ┐    ┌     ┐┌   ┐
    │Skl│    │c  −s││Skl│
    │   │ := │     ││   │
    │Sij│    │s   c││Sij│
    └   ┘    └     ┘└   ┘
  endproc

  ! init e, E, and arrays ind, changed
  E := I; state := n
  for k := 1 to n do indk := maxind(k); ek := Skk; changedk := true endfor
  while state≠0 do ! next rotation
    m := 1 ! find index (k,l) of pivot p
    for k := 2 to n−1 do
      if │Sk indk│ > │Sm indm│ then m := k endif
    endfor
    k := m; l := indm; p := Skl
    ! calculate c = cos φ, s = sin φ
    y := (el−ek)/2; d := │y│+√(p2+y2)
    r := √(p2+d2); c := d/r; s := p/r; t := p2/d
    if y<0 then s := −s; t := −t endif
    Skl := 0.0; update(k,−t); update(l,t)
    ! rotate rows and columns k and l
    for i := 1 to k−1 do rotate(i,k,i,l) endfor
    for i := k+1 to l−1 do rotate(k,i,i,l) endfor
    for i := l+1 to n do rotate(k,i,l,i) endfor
    ! rotate eigenvectors
    for i := 1 to n do
      ┌   ┐    ┌     ┐┌   ┐
      │Eik│    │c  −s││Eik│
      │   │ := │     ││   │
      │Eil│    │s   c││Eil│
      └   ┘    └     ┘└   ┘
    endfor
    ! update all potentially changed indi
    for i := 1 to n do indi := maxind(i) endfor
  loop
endproc




template <typename T, size_t N>
std::array<T, N> jacobi(Matrix<T, N> S, Matrix<T, N>& E) {
    std::array<T, N> e = {0}; // initialize eigenvalues to zero
    std::array<size_t, N> ind; // largest off-diagonal index for each row
    std::array<bool, N> changed; // keep track of changed rows
    std::fill(changed.begin(), changed.end(), true); // mark all rows as changed

    E = eye<T, N>(); // initialize eigenvector matrix to the identity matrix
    size_t state = N; // number of rows still changing

    // maxind function
    auto maxind = [&](const size_t k) -> size_t {
        size_t m = k + 1;
        for (size_t i = k + 2; i < N; ++i) {
            if (std::abs(S[k][ind[k]]) < std::abs(S[k][i])) {
                m = i;
            }
        }
        return m;
    };

    // update function
    auto update = [&](const size_t k, const T t) {
        T y = e[k];
        e[k] += t;
        if (changed[k] && (y == e[k])) {
            changed[k] = false;
            --state;
        } else if (!changed[k] && (y != e[k])) {
            changed[k] = true;
            ++state;
        }
    };

    // rotate function
    auto rotate = [&](const size_t k, const size_t l, const size_t i, const size_t j) {
        T c, s, t;
        if (S[k][l] == 0) {
            c = 1;
            s = 0;
        } else {
            T tau = (S[l][l] - S[k][k]) / (2 * S[k][l]);
            t = (tau > 0) ? 1 / (tau + std::sqrt(1 + tau * tau))
                           : -1 / (-tau + std::sqrt(1 + tau * tau));
            c = 1 / std::sqrt(1 + t * t);
            s = t * c;
        }
        T a_kk = S[k][k];
        T a

} // namespace scipp::geometry