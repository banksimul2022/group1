var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const helmet = require('helmet');
const cors = require('cors');
const userRouter = require('./routes/user');
//const basicAuth = require('express-basic-auth');


var app = express();
//app.use(basicAuth({users: { 1 : 1}}))
app.set('view engine', 'ejs');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname + 'public')));
app.use(helmet());
app.use(cors());

app.use('/user', userRouter);

app.get('/', function(req, res) { //render homepage
  res.render('home');
});

module.exports = app;
