// Versor Geometric Algebra Library
// Copyright (c) 2017 Lars Tingelstad
// Copyright (c) 2010 Pablo Colapinto
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// The views and conclusions contained in the software and documentation are
// those of the authors and should not be interpreted as representing official
// policies, either expressed or implied, of the FreeBSD Project.

#pragma once

#include <versor/detail/basis.h>

namespace vsr {

/** The value type of data (default is double) */
#define VSR_PRECISION double

/*-----------------------------------------------------------------------------
 *  Lowest level product for when to Flip product, calculate inner, or calculate
 *outer
 *-----------------------------------------------------------------------------*/
template <bits::type A, bits::type B> struct product {
  static const bits::type result = A ^ B;
  static const bool is_positive = !bits::signFlip(A, B);
  static const bool has_inner = bits::inner(A, B);
  static const bool has_outer = bits::outer(A, B);
};

/*-----------------------------------------------------------------------------
 *  use of product to calculate value
 *-----------------------------------------------------------------------------*/
template <bool positive, int idxA, int idxB> struct binary_function_token {
  template <class TA, class TB>
  static constexpr typename TA::value_t Exec(const TA &a, const TB &b) {
    return a[idxA] * b[idxB] * (positive ? 1 : -1);
  }
  static void print() {
    printf(" %s a[%d] * b[%d] \t", positive ? "" : "-", idxA, idxB);
  }
};

// template<bool positive, int idxA, int idxB>
// struct print< binary_function_token<positive, idxA, idxB> >{
//  static void print(){
//    printf(" a[%d] * b[%d] /*%s*/\t", idxA, idxB,
//    bits::estring(product::result).c_str() );
//  }
//};

template <bool positive, int idx> struct unary_function_token {
  template <class TA> static constexpr typename TA::value_t Exec(const TA &a) {
    return a[idx] * (positive ? 1 : -1);
  }
  static void print() { printf("%s\ta[%d]\t", (positive ? "" : "-"), idx); }
};

/*-----------------------------------------------------------------------------
 *  Single Word of an Instruction -- multiples a[IDXA] by b[IDXB]
 *-----------------------------------------------------------------------------*/
template <bool Flip, int IDXA, int IDXB> struct Instruction {
  static const int Sign = Flip ? -1 : 1;

  template <class TA, class TB>
  static constexpr typename TA::algebra::value_t Exec(const TA &a,
                                                      const TB &b) {
    return Sign * a[IDXA] * b[IDXB];
  }

  static void print() { printf("%d * a[%d] * b[%d]", Sign, IDXA, IDXB); }
};

template <bool F, bits::type A, bits::type B, int IDXA, int IDXB> struct Inst {
  static const bits::type Res = A ^ B;
  static const bool IP = bits::inner(A, B);
  static const bool OP = bits::outer(A, B);

  template <class TA, class TB>
  static constexpr typename TA::algebra::value_t Exec(const TA &a,
                                                      const TB &b) {
    return a[IDXA] * b[IDXB];
  }

  static void print() {
    printf(" a[%d] * b[%d] /*%s*/\t", IDXA, IDXB, bits::estring(Res).c_str());
  }
};

template <bits::type A, bits::type B, int IDXA, int IDXB>
struct Inst<true, A, B, IDXA, IDXB> {
  static const bits::type Res = A ^ B;
  static const bool IP = bits::inner(A, B);
  static const bool OP = bits::outer(A, B);

  template <class TA, class TB>
  static constexpr typename TA::algebra::value_t Exec(const TA &a,
                                                      const TB &b) {
    return -a[IDXA] * b[IDXB];
  }

  static void print() {
    printf("-a[%d] * b[%d] /*%s*/\t", IDXA, IDXB, bits::estring(Res).c_str());
  }
};

// ok, like Inst but without the product calculations inside it (assumes RULE
// has been invoked)
template <bool F, bits::type R, int IDXA, int IDXB> struct Instruct {
  static const bits::type Res = R;
  static const int idxA = IDXA;
  static const int idxB = IDXB;

  template <class TA, class TB>
  static constexpr typename TA::algebra::value_t Exec(const TA &a,
                                                      const TB &b) {
    return a[idxA] * b[idxB];
  }
  static void print() {
    printf(" a[%d] * b[%d] /*%s*/\t", idxA, idxB, bits::estring(Res).c_str());
  }
};
template <bits::type R, int IDXA, int IDXB>
struct Instruct<true, R, IDXA, IDXB> {
  static const bits::type Res = R;
  static const int idxA = IDXA;
  static const int idxB = IDXB;

  template <class TA, class TB>
  static constexpr typename TA::algebra::value_t Exec(const TA &a,
                                                      const TB &b) {
    return -a[idxA] * b[idxB];
  }
  static void print() {
    printf("-a[%d] * b[%d] /*%s*/\t", idxA, idxB, bits::estring(Res).c_str());
  }
};

/*-----------------------------------------------------------------------------
 *  Single Token of a Sign Flip Instruction
 *-----------------------------------------------------------------------------*/
template <bool F, int IDX> struct InstFlip {
  template <class TA>
  static constexpr typename TA::algebra::value_t Exec(const TA &a) {
    return a[IDX];
  }
  static void print() { printf("a[%d]\t", IDX); }
};
template <int IDX> struct InstFlip<true, IDX> {
  template <class TA>
  static constexpr typename TA::algebra::value_t Exec(const TA &a) {
    return -a[IDX];
  }
  static void print() { printf("-a[%d]\t", IDX); }
};

/*-----------------------------------------------------------------------------
 *  Single Token of a Casting Instruction
 *-----------------------------------------------------------------------------*/
template <int IDX> struct InstCast {
  template <class TA>
  static constexpr typename TA::algebra::value_t Exec(const TA &a) {
    return a[IDX];
  }
};
template <> struct InstCast<-1> {
  template <class TA>
  static constexpr typename TA::algebra::value_t Exec(const TA &a) {
    return 0;
  }
};
}
