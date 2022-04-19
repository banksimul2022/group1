require('dotenv').config();
const path = require('path')

const mysql = require('mysql');
const connection = mysql.createPool({
  host: process.env.HOST,
  user: process.env.USER,
  password: process.env.SQLPASS, 
  database: process.env.DATABASE
});

module.exports = connection;