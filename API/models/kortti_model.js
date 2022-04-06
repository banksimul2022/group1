const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const Kortti={
  get: function(callback) {
    return db.query('select * from Kortti', callback); //haetaan paskaa
  },
  getByCardNumber: function(Korttinumero, callback) { //haetaan kortin pin
    return db.query('select PIN from Kortti where Korttinumero=?', [Korttinumero], callback);
  },
  add: function(Kortti, callback) { //lisätään Kortti tietokantaan
    bcrypt.hash(Kortti.PIN, saltRounds, function(err, hash) {
      return db.query('insert into Kortti (Korttinumero, PIN, Asiakas_IDAsiakas, Tili_idTili) values(?,?,?,?)',
      [Kortti.Korttinumero, hash, Kortti.Asiakas_IDAsiakas, Kortti.Tili_idTili], callback);
    })
  }

}
          
module.exports = Kortti;