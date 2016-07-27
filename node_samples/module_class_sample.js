// singleobject.js

function Hello() {
	var name;

	this.setName = function( thyName ) {
		name = thyName;
	};

	this.sayHello = function() {
		console.log( 'Hello ' + name );
	};
};

exports.Hello = Hello;


// refModule.js

require( './singleobject').Hello



// 略显冗余
// 使用如下方式

// hello.js
function Hello() {
	var name;

	this.setName = function( thyName ) {
		name = thyName;
	}

	this.sayHello = function() {
		console.log( 'Hello ' + name );
	};
};

module.exports = Hello;


// refHello.js

var Hello = require( './hello' );

hello = new Hello();
hello.setName( 'BYVoid' );
hello.sayHello();