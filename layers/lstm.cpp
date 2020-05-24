#include "lstm.h"

namespace ml
{
  lstm::lstm( size_t iSize, size_t oSize ) {

    Xt = vector( iSize );
    Ht = vector( oSize );
    Ct = vector( oSize );

    Wf = trainable_matrix( oSize, iSize );
    Wi = trainable_matrix( oSize, iSize );
    Wo = trainable_matrix( oSize, iSize );
    Wc = trainable_matrix( oSize, iSize );

    Uf = trainable_matrix( oSize, oSize );
    Ui = trainable_matrix( oSize, oSize );
    Uc = trainable_matrix( oSize, oSize );
    Uo = trainable_matrix( oSize, oSize );
  }

  size_t lstm::inputSize() const {
    return Xt.size();
  }

  size_t lstm::outputSize() const {
    return Ht.size();
  }

  void lstm::setInput( const vector& input ) {
    for ( size_t i = 0; i < Xt.size(); i++ ) {
      Xt[i] = input[i];
    }
  }

  const vector& lstm::getOutput() const {
    return Ht;
  }

  void lstm::activate() {

    /*
    True code. Commented out for experimental reasons.


    vector HtXt = Ht.append( Xt );

    vector ft = sigmoid( WeightF * HtXt + BiasF );
    vector it = sigmoid( WeightI * HtXt + BiasI );
    vector ct = tanh( WeightC * HtXt + BiasC );
    vector ot = sigmoid( WeightO * HtXt + BiasO );

    Ct = Ct * ft + ct * it;
    Ht = tanh( Ct ) * ot;
    */

    /*
    timestep_meta meta1;
    Xt[0] = 1;
    Xt[1] = 2;
    meta1.xt = Xt;

    meta1.ft = sigmoid( Wf * Xt + Uf * Ht + BiasF );
    meta1.it = sigmoid( Wi * Xt + Ui * Ht + BiasI );
    meta1.ct = tanh( Wc * Xt + Uc * Ht + BiasC );
    meta1.ot = sigmoid( Wo * Xt + Uo * Ht + BiasO );

    Ct = Ct * meta1.ft + meta1.ct * meta1.it;
    Ht = tanh( Ct ) * meta1.ot;
    meta1.ht = Ht;
    meta1.Eout = vector( 1 );
    meta1.Eout[0] = Ht[0] - 0.5;

    timestep_meta meta2;
    Xt[0] = 0.5;
    Xt[1] = 3;
    meta2.xt = Xt;

    meta2.ft = sigmoid( Wf * Xt + Uf * Ht + BiasF );
    meta2.it = sigmoid( Wi * Xt + Ui * Ht + BiasI );
    meta2.ct = tanh( Wc * Xt + Uc * Ht + BiasC );
    meta2.ot = sigmoid( Wo * Xt + Uo * Ht + BiasO );

    Ct = Ct * meta2.ft + meta2.ct * meta2.it;
    Ht = tanh( Ct ) * meta2.ot;
    meta2.ht = Ht;
    meta2.Eout = vector( 1 );
    meta2.Eout[0] = Ht[0] - 1.25;


    vector eout = meta2.Eout + 0;
    vector eo = eout * tanh( Ct ) * meta2.ot * ( 1 - meta2.ot );
    vector ect = eout * meta2.ot * ( 1 - pow( tanh( Ct ), 2 ) );
    vector ecv = ect * meta2.it * ( 1 - pow( meta2.ct, 2 ) );
    //vector ei = ect * meta2.ct * meta2.it * ( meta2.it - 1 ) * -1;

    */
  }

  void lstm::learn( const vector& error, double learningRate ) {

  }

  void lstm::applyLearnings() {

  }

}
