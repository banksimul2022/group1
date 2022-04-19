const db = require('../database');

const tili = {
    get: function (callback) {
        return db.query('select * from Tili', callback);
    },
    getById: function (id, callback) {
        return db.query('select * from Tili where idTili=?', [id], callback);
    },
    add: function(tili, callback) {
        return db.query(
          'insert into Tili (Tilinumero, Saldo) values(?,?)',
          [tili.Tilinumero, tili.Saldo], callback
        );
    }
    
}

module.exports = tili;