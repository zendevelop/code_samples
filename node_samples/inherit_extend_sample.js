// inheritance helper;
function extend( Child, Parent ) {
	var F = function() {};
	F.prototype = Parent.prototype;
	Child.prototype = new F();
	Child.prototype.constructor = Child;
	Child.uber = Parent.prototype;
}

function Shape() {};
Shape.prototype.name = 'Shape';
Shape.prototype.toString = function() {
	return this.constructor.uber ?
		this.constructor.uber.toString() + ', ' + this.name : this.name;
};


function TwoDShape() {};
extend( TwoDShape, Shape );
TwoDShape.prototype.name = '2D shape';

function Triangle( side, height ) {
	this.side = side;
	this.height = height;
}
extend( Triangle, TwoDShape );
Triangle.prototype.name = 'Triangle';
Triangle.prototype.getArea = function() {
	return this.side * this.height / 2;
}


// Test
new Triangle().toString();
// 'Shape, 2D shape, Triangle'