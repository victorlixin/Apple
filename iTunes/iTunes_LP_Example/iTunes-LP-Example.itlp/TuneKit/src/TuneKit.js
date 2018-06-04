/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

const TK_VERSION = '2009-11-19';

/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

/**
 *  The keyboard identifier for the backspace key.
 *  @constant
 *  @type int
 */
const KEYBOARD_BACKSPACE = 8;
/**
 *  The keyboard identifier for the left key.
 *  @constant
 *  @type int
 */
const KEYBOARD_LEFT = 37;
/**
 *  The keyboard identifier for the right key.
 *  @constant
 *  @type int
 */
const KEYBOARD_RIGHT = 39;
/**
 *  The keyboard identifier for the up key.
 *  @constant
 *  @type int
 */
const KEYBOARD_UP = 38;
/**
 *  The keyboard identifier for the down key.
 *  @constant
 *  @type int
 */
const KEYBOARD_DOWN = 40;
/**
 *  The keyboard identifier for the return key.
 *  @constant
 *  @type int
 */
const KEYBOARD_RETURN = 13;

/**
 *  Indicates whether TuneKit is running on Apple TV.
 *  @constant
 *  @type bool
 */
const IS_APPLE_TV = (window.iTunes !== undefined && window.iTunes.platform == 'AppleTV');
/**
 *  The Apple TV-specific iTunes system sounds interface.
 *  @constant
 *  @type bool
 *  @private
 */
const ATV_SOUNDS = IS_APPLE_TV ? window.iTunes.getSystemSounds() : null;

/**
 *  The move sound of the Apple TV user interface.
 *  @constant
 *  @type Object
 */
const SOUND_MOVED = IS_APPLE_TV ? ATV_SOUNDS.SystemSoundScrollStart : new Audio('TuneKit/sounds/SelectionChange.aif');
/**
 *  The selection sound of the Apple TV user interface.
 *  @constant
 *  @type Object
 */
const SOUND_ACTIVATED = IS_APPLE_TV ? ATV_SOUNDS.SystemSoundSelect : new Audio('TuneKit/sounds/Selection.aif');
/**
 *  The limit sound of the Apple TV user interface.
 *  @constant
 *  @type Object
 */
const SOUND_LIMIT = IS_APPLE_TV ? ATV_SOUNDS.SystemSoundScrollLimit : new Audio('TuneKit/sounds/Limit.aif');
/**
 *  The exit sound of the Apple TV user interface.
 *  @constant
 *  @type Object
 */
const SOUND_EXIT = IS_APPLE_TV ? ATV_SOUNDS.SystemSoundExit : new Audio('TuneKit/sounds/Exit.aif');

/**
 *  @class
 *  @name TKUtils
 *
 *  @since TuneKit 1.0
 */
function TKUtils () {
};

/* ==================== SOUNDS ==================== */

/**
 *  Plays a sound.
 *
 *  @param {Object} sound The sound to play, which is either an <code>audio</code> element or an iTunes system sound identifier on Apple TV.
 */
TKUtils.playSound = function (sound) {
  if (IS_APPLE_TV) {
    ATV_SOUNDS.playSystemSound(sound);
  }
  else {
    sound.play();
  }
};

/* ==================== TRANSFORMS SHORTHANDS ==================== */

/**
 *  Prints a <code>translate3d()</code> command that can be used as input for a <code>-webkit-transform</code> property.
 *  
 *  @param {int} tx The x coordinate for the translation.
 *  @param {int} ty The y coordinate for the translation
 *
 *  @returns {String} The <code>translate3d()</code> command
 */
TKUtils.t = function (tx, ty) {
  return 'translate3d(' + tx + 'px, ' + ty + 'px, 0)';
};

/**
 *  Creates a CSS string representation for a number in pixels.
 *  
 *  @param {number} value The value to be converted.
 *
 *  @returns {String} A CSS string representation for <code>value</code> in pixels.
 */
TKUtils.px = function (value) {
  return value + 'px';
};

/* ==================== Array ==================== */

/**
 *  Copies all properties from one object onto another.
 *  
 *  @param {Object} sourceObject The object from which we will copy properties.
 *  @param {Object} targetObject The array onto which we will copy properties.
 */
TKUtils.copyPropertiesFromSourceToTarget = function (source, target) {
  for (var property in source) {
    target[property] = source[property];
  }
};

/* ==================== Delegates ==================== */

/**
 *  Indicates whether an object is a <code>Function</code>.
 *  
 *  @param {Object} object The object purported to be a <code>Function</code>.
 *
 *  @returns {bool} Whether the object is a <code>Function</code>.
 */
TKUtils.objectIsFunction = function (object) {
  return (typeof object == 'function');
};

/**
 *  Indicates whether an object is <code>undefined</code>.
 *  
 *  @param {Object} object The object purported to be <code>undefined</code>.
 *
 *  @returns {bool} Whether the object is <code>undefined</code>.
 */
TKUtils.objectIsUndefined = function (object) {
  return (object === undefined);
};

/**
 *  Indicates whether an object is a string literal or a <code>String</code> instance.
 *  
 *  @param {Object} object The object purported to be a string literal or a <code>String</code> instance.
 *
 *  @returns {bool} Whether the object is a string literal or a <code>String</code> instance.
 */
TKUtils.objectIsString = function (object) {
  return (typeof object == 'string' || object instanceof String);
};

/**
 *  Indicates whether an object is an <code>Array</code>.
 *  
 *  @param {Object} object The object purported to be an <code>Array</code>.
 *
 *  @returns {bool} Whether the object is an <code>Array</code>.
 */
TKUtils.objectIsArray = function (object) {
  return (object instanceof Array);
};

/**
 *  Indicates whether an object implements a given method, useful to check if a delegate
 *  object implements a given delegate method.
 *  
 *  @param {Object} object The object purported to implement a given method.
 *  @param {String} methodNameAsString The method name as a <code>String</code>.
 *
 *  @returns {bool} Whether the object implements the given method.
 */
TKUtils.objectHasMethod = function (object, methodNameAsString) {
  return (  object !== null &&
            !this.objectIsUndefined(object) &&
            !this.objectIsUndefined(object[methodNameAsString]) &&
            this.objectIsFunction(object[methodNameAsString])
         );
};

/* ==================== INIT ==================== */

/**
 *  Sets up the .displayNames for all functions defined on the specified class, including its prototype.
 *  
 *  @param {Object} class The class.
 *  @param {String} className The class name as a string, in case it can not be derived from <code>class</code>. Optional.
 */
TKUtils.setupDisplayNames = function (object, className) {
  var class_name = className || object.name;
  for (var i in object) {
    // make sure we don't touch properties that were synthetized
    if (object.__lookupGetter__(i)) {
      continue;
    }
    var prop = object[i];
    if (TKUtils.objectIsFunction(prop)) {
      prop.displayName = TKUtils.createDisplayName(class_name, i);
    }
  }
  for (var i in object.prototype) {
    // make sure we don't touch properties that were synthetized
    if (object.prototype.__lookupGetter__(i)) {
      continue;
    }
    var prop = object.prototype[i];
    if (TKUtils.objectIsFunction(prop)) {
      prop.displayName = TKUtils.createDisplayName(class_name, i);
    }
  }
};

TKUtils.createDisplayName = function (className, methodName) {
  return className + '.' + methodName + '()';
};

TKUtils.buildElement = function (elementData) {
  // nothing to do if we don't have useful data
  if (!elementData || !elementData.type) {
    return null;
  }
  //
  var element = null;
  switch (elementData.type) {
    case "emptyDiv":
      element = document.createElement("div");
      break;
    case "container":
      element = document.createElement("div");
      for (var i=0; i < elementData.children.length; i++) {
        element.appendChild(TKUtils.buildElement(elementData.children[i]));
      }
      break;
    case "image":
      element = document.createElement("img");
      element.src = elementData.src;
      break;
    case "text":
      element = document.createElement("div");
      var p = document.createElement("p");
      p.innerText = elementData.text;
      element.appendChild(p);
      break;
    default:
      element = document.createElement(elementData.type);
      element.innerHTML = elementData.content;
  }
  // add optional id 
  if (elementData.id) {
    element.id = elementData.id;
  }
  // add optional class 
  if (elementData.className) {
    element.className = elementData.className;
  }
  
  // wrap in optional link
  if (elementData.link){
    var subElement = element;
    element = document.createElement("a");
    element.href = elementData.link;
    element.target = "_blank";
    element.appendChild(subElement);
  }
  
  return element;
};

/**
 *  Creates a DOM event.
 *
 *  @param {String} eventType The event type.
 *  @param {Element} relatedTarget The optional related target for this event.
 *
 *  @returns {Event} The event.
 */
TKUtils.createEvent = function (eventType, relatedTarget) {
  var event = document.createEvent('Event');
  event.initEvent(eventType, true, true);
  event.relatedTarget = relatedTarget;
  return event;
};

/**
 *  Indicates whether a node is in some other node's subtree.
 *
 *  @param {Node} childNode The alleged child node.
 *  @param {Node} allegedParentNode The alleged parent node.
 *
 *  @returns {bool} Whether <code>childNode</code> is a child of <code>allegedParentNode</code>.
 */
TKUtils.isNodeChildOfOtherNode = function (childNode, allegedParentNode) {
  var node = childNode.parentNode;
  while (node !== null) {
    if (node === allegedParentNode) {
      return true;
      break;
    }
    node = node.parentNode;
  }
  return false;
};

TKUtils.setupDisplayNames(TKUtils, 'TKUtils');

/* ==================== TKRect ==================== */

/**
 *  The top left corner of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectTopLeftCorner = 0;
/**
 *  The middle point on the top edge of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectMiddleOfTopEdge = 1;
/**
 *  The top right corner of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectTopRightCorner = 2;
/**
 *  The middle point on the right edge of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectMiddleOfRightEdge = 3;
/**
 *  The bottom right corner of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectBottomRightCorner = 4;
/**
 *  The middle point on the bottom edge of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectMiddleOfBottomEdge = 5;
/**
 *  The bottom left corner of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectBottomLeftCorner = 6;
/**
 *  The middle point on the left edge of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectMiddleOfLeftEdge = 7;
/**
 *  The center of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectCenter = 8;
/**
 *  The top edge of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectTopEdge = 9;
/**
 *  The right edge of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectRightEdge = 10;
/**
 *  The bottom edge of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectBottomEdge = 11;
/**
 *  The left edge of a rectangle.
 *  @constant
 *  @type int
 *  @private
 */
const TKRectLeftEdge = 12;

/**
 *  @class
 *
 *  <p>The <code>TKRect</code> provides some utilities to deal with a rectangle data type, allowing to obtain coordinates of the rectangle's points
 *  of interest as {@link TKPoint} objects and its edges as {@link TKSegment} objects, or obtaining a rectangle resulting in the union of several others.</p>
 *
 *  @since TuneKit 1.0
 *
 *  @param {float} x The x coordinate.
 *  @param {float} y The y coordinate.
 *  @param {float} width The width.
 *  @param {float} height The height.
 */
function TKRect (x, y, width, height) {
  /**
   *  The x coordinate.
   *  @type float
   */
  this.x = x || 0;
  /**
   *  The y coordinate.
   *  @type float
   */
  this.y = y || 0;
  /**
   *  The width.
   *  @type float
   */
  this.width = width || 0;
  /**
   *  The height.
   *  @type float
   */
  this.height = height || 0;
};

/**
 *  @private
 *  Provides the coordinates of a given point of interest.
 *
 *  @param {int} index The point of interest.
 *
 *  @returns {TKPoint} The point at the given point of interest.
 */
TKRect.prototype.pointAtPosition = function (index) {
  var point;
  if (index == TKRectTopLeftCorner) {
    point = new TKPoint(this.x, this.y);
  }
  else if (index == TKRectMiddleOfTopEdge) {
    point = new TKPoint(this.x + this.width / 2, this.y);
  }
  else if (index == TKRectTopRightCorner) {
    point = new TKPoint(this.x + this.width, this.y);
  }
  else if (index == TKRectMiddleOfRightEdge) {
    point = new TKPoint(this.x + this.width, this.y + this.height / 2);
  }
  else if (index == TKRectBottomRightCorner) {
    point = new TKPoint(this.x + this.width, this.y + this.height);
  }
  else if (index == TKRectMiddleOfBottomEdge) {
    point = new TKPoint(this.x + this.width / 2, this.y + this.height);
  }
  else if (index == TKRectBottomLeftCorner) {
    point = new TKPoint(this.x, this.y + this.height);
  }
  else if (index == TKRectMiddleOfLeftEdge) {
    point = new TKPoint(this.x, this.y + this.height / 2);
  }
  else if (index == TKRectCenter) {
    point = new TKPoint(this.x + this.width / 2, this.y + this.height / 2);
  }
  return point;
};

/**
 *  @private
 *  Provides the segment for a given edge.
 *
 *  @param {int} index The edge.
 *
 *  @returns {TKSegment} The segment for the given edge.
 */
TKRect.prototype.edge = function (index) {
  var edge;
  if (index == TKRectTopEdge) {
    edge = new TKSegment(this.pointAtPosition(TKRectTopLeftCorner), this.pointAtPosition(TKRectTopRightCorner));
  }
  else if (index == TKRectRightEdge) {
    edge = new TKSegment(this.pointAtPosition(TKRectTopRightCorner), this.pointAtPosition(TKRectBottomRightCorner));
  }
  else if (index == TKRectBottomEdge) {
    edge = new TKSegment(this.pointAtPosition(TKRectBottomLeftCorner), this.pointAtPosition(TKRectBottomRightCorner));
  }
  else if (index == TKRectLeftEdge) {
    edge = new TKSegment(this.pointAtPosition(TKRectTopLeftCorner), this.pointAtPosition(TKRectBottomLeftCorner));
  }
  return edge;
};

/**
 *  Returns a {@link TKRect} from a rectangle returned by the <code>Node.getBoundingClientRect</code> method.
 *
 *  @param {ClientRect} rect The CSS client rectangle.
 *
 *  @returns {TKRect} The equivalent rectangle as a TuneKit data type.
 */
TKRect.rectFromClientRect = function (rect) {
  return new TKRect(rect.left, rect.top, rect.width, rect.height);
};

/**
 *  @private
 *  Returns a {@link TKRect} encompassing the union of a list of other rectangles.
 *
 *  @param {Array} rects The various rectangles we'd like the union of.
 *
 *  @returns {TKRect} The rectangle encompassing the union of a list of the provided rectangles.
 */
TKRect.rectFromUnionOfRects = function (rects) {
  if (rects.length < 1) {
    return new TKRect();
  }
  var union = rects[0];
  var rect;
  for (var i = 1; i < rects.length; i++) {
    rect = rects[i];
    union.x = Math.min(union.x, rect.x);
    union.y = Math.min(union.y, rect.y);
    union.width = Math.max(union.width, rect.x + rect.width);
    union.height = Math.max(union.height, rect.y + rect.height);
  }
  return union;
};

/* ==================== TKPoint ==================== */

/**
 *  @private
 *  @class
 *
 *  <p>The <code>TKPoint</code> provides a TuneKit data type to deal with points in 2D space and some utilities to work with them, such as figuring out
 *  the distance between two points.</p>
 *
 *  @since TuneKit 1.0
 *
 *  @param {float} x The x coordinate.
 *  @param {float} y The y coordinate.
 */
function TKPoint (x, y) {
  /**
   *  The x coordinate.
   *  @type float
   */
  this.x = x || 0;
  /**
   *  The y coordinate.
   *  @type float
   */
  this.y = y || 0;
};

/**
 *  Provides the distance between this point and another.
 *
 *  @param {TKPoint} aPoint The point to which we'd like to figure out the distance.
 *
 *  @returns {float} The distance between the receiver the provided point.
 */
TKPoint.prototype.distanceToPoint = function (aPoint) {
  return Math.sqrt(Math.pow(aPoint.x - this.x, 2) + Math.pow(aPoint.y - this.y, 2));
};

/* ==================== TKSegment ==================== */

/**
 *  @class
 *  @private
 *
 *  <p>The <code>TKSegment</code> provides a TuneKit data type to deal with segments in 2D space and some utilities to work with them, such as figuring out
 *  the shortest distance between a segment and a point.</p>
 *
 *  @since TuneKit 1.0
 *
 *  @param {TKPoint} a The first extremity of the segment.
 *  @param {TKPoint} b The other extremity of the segment.
 */
function TKSegment (a, b) {
  /**
   *  The first extremity of the segment.
   *  @type TKPoint
   */
  this.a = a;
  /**
   *  The other extremity of the segment.
   *  @type TKPoint
   */
  this.b = b;
  this.ab = new TKPoint(b.x - a.x, b.y - a.y);
  /**
   *  The segment's length.
   *  @type float
   */
  this.length = b.distanceToPoint(a);
};

// XXX: this only deals with horizontal and vertical lines
TKSegment.prototype.crossPoint = function (c) {
  return (this.a.y == this.b.y) ? new TKPoint(c.x, this.a.y) : new TKPoint(this.a.x, c.y);
};

/**
 *  Computes the shortest distance between this segment and the given point.
 *
 *  @param {TKPoint} aPoint
 *
 *  @returns {float} The shortest distance between this segment and the given point.
 */
TKSegment.prototype.distanceToPoint = function (aPoint) {
  var d;
  var cross_point = this.crossPoint(aPoint);
  // is it inside the segment?
  if (cross_point.distanceToPoint(this.a) + cross_point.distanceToPoint(this.b) == this.length) {
    d = aPoint.distanceToPoint(cross_point);
  }
  else {
    d = Math.min(aPoint.distanceToPoint(this.a), aPoint.distanceToPoint(this.b));
  }
  return d;
};

/* ================= Debugging ======================== */

var DEBUG = false;

function debug(msg) {
  if (window.DEBUG !== undefined && window.DEBUG) {
    console.log("DEBUG: " + msg);
  }
};
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

/**
 *  @class
 *
 *  <p>The TKClass function will process a constructor function and set up its inheritance chain, synthetize
 *  a number of its instance properties and mix in additional capabilities based properties defined on
 *  that function. The supported properties are:</p>
 *
 *  <ul>
 *    <li><code>inherits</code> – the superclass</li>
 *    <li><code>includes</code> – an Array of modules to pull in</li>
 *    <li><code>synthetizes</code> – an Array of properties to synthetize</li>
 *  </ul>
 *
 *  <p>For instance, consider the following class declaration:</p>
 *
 *  <pre class="example">
// extends MySuperClass
MyClass.inherits = MySuperClass;

// mixes in the TKEventTriage and TKPropertyTriage modules
MyClass.includes = [TKEventTriage, TKPropertyTriage]; 

// synthetizes the .foo and .bar properties
MyClass.synthetizes = ['foo', 'bar'];

function MyClass () {
  // constructor code goes here
};

// process properties set up on the MyClass constructor
TKClass(MyClass);
 *  </pre>
 *
 *  <p>Synthetization is fully automated as long as the class that wishes to offer synthetized properties follows
 *  the following rules:</p>
 *
 *  <ul>
 *    <li>say the class wishes to synthetize the property <code>.foo</code></li>
 *    <li>if the class chooses to define a getter method, it must be defined as <code>getFoo</code> on its <code>prototype</code>
 *    <li>if the class chooses to define a setter method, it must be defined as <code>setFoo</code> on its <code>prototype</code>
 *    <li>the class must define an instance variable <code>._foo</code> which is the internal object that the class is responsible to update if either a setter is specified</li>
 *  </ul>
 *
 *  <p>So our previous class declaration could be extended as follows:</p>
 *
 *  <pre class="example">
function MyClass () {
  this._foo = '';
};

// custom setter for .foo, the getter is not specified
// and TKClass() will automatically create it
MyClass.prototype.setFoo = function (newFooValue) {
  this._foo = newFooValue;
};

// custom getter for .foo, the setter is not specified
// and TKClass() will automatically create it
MyClass.prototype.getBar = function (newFooValue) {
  return 'Hello ' + this._foo;
};
 *  </pre>
 *
 *  @since TuneKit 1.0
 *
 *  @constructor
 *  @param theClass {Object} The class.
 */

function TKClass (theClass) {
  // check out if we have inheritance set up, otherwise, make TKObject the default superclass
  if (TKUtils.objectIsUndefined(theClass.inherits) && theClass !== TKObject) {
    theClass.inherits = TKObject;
  }
  
  // check out if we have mixins
  if (theClass.includes) {
    TKClass.mixin(theClass.prototype, theClass.includes);
  }

  // synthetizes properties defined locally
  var properties = (theClass.synthetizes) ? theClass.synthetizes : [];
  // now synthetize
  for (var i = 0; i < properties.length; i++) {
    TKClass.synthetizeProperty(theClass.prototype, properties[i], true);
  }

  // synthetizes properties by compiling them up the inheritance chain
  var aClass = theClass;
  var properties = [];
  while (aClass.inherits) {
    aClass = aClass.inherits;
    if (aClass.synthetizes) {
      properties = aClass.synthetizes.concat(properties);
    }            
  }
  // now synthetize
  for (var i = 0; i < properties.length; i++) {
    TKClass.synthetizeProperty(theClass.prototype, properties[i], false);
  }

  // go through each method and save its name as a custom property
  // that we'll use later in TKObject.callSuper()
  for (var i in theClass.prototype) {
    // make sure we don't touch properties that were synthetized
    if (theClass.prototype.__lookupGetter__(i)) {
      continue;
    }
    var prop = theClass.prototype[i];
    if (TKUtils.objectIsFunction(prop)) {
      prop._class = theClass;
      prop._name = i;
      prop.displayName = TKUtils.createDisplayName(theClass.name, i);
    }
  }

  // inherit from the superclass
  // default to TKObject if nothing is specified
  if (theClass !== TKObject) {
    theClass.prototype.__proto__ = theClass.inherits.prototype;
  }
};

TKClass.synthetizeProperty = function (object, propertyName, isPropertyInherited) {
  var camel_ready = propertyName.charAt(0).toUpperCase() + propertyName.substr(1);
  var getter_name = 'get' + camel_ready;
  var setter_name = 'set' + camel_ready;
  // check on function availability
  var has_getter = TKUtils.objectHasMethod(object, getter_name);
  var has_setter = TKUtils.objectHasMethod(object, setter_name);
  
  // if we have neither a getter or a setter, then do nothing
  // unless the property is defined locally
  if (!isPropertyInherited && !(has_getter || has_setter)) {
    return;
  }
  
  // assign the setter function if we have one
  if (has_setter) {
    var specified_setter_function = function (newValue) {
      object[setter_name].call(this, newValue);
      this.notifyPropertyChange(propertyName);
    };
    specified_setter_function.displayName = 'Specified setter for .' + propertyName + ' on ' + object.constructor.name;
    object.__defineSetter__(propertyName, specified_setter_function);
  }
  // otherwise just assign to _propertyName
  else {
    var default_setter_function = function (newValue) {
      this['_' + propertyName] = newValue;
      this.notifyPropertyChange(propertyName);
    };
    default_setter_function.displayName = 'Default setter for .' + propertyName + ' on ' + object.constructor.name;
    object.__defineSetter__(propertyName, default_setter_function);
  }
  
  // assign the getter function if we have one
  if (has_getter) {
    object.__defineGetter__(propertyName, object[getter_name]);
  }
  // otherwise just return _propertyName
  else {
    var default_getter_function = function () {
      return this['_' + propertyName];
    };
    default_getter_function.displayName = 'Default getter for .' + propertyName + ' on ' + object.constructor.name;
    object.__defineGetter__(propertyName, default_getter_function);
  }
};

TKClass.mixin = function (target, sources) {
  for (var i = 0; i < sources.length; i++) {
    TKUtils.copyPropertiesFromSourceToTarget(sources[i], target);
  }
};

TKUtils.setupDisplayNames(TKClass, 'TKClass');
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

/**
 *  @class
 *  @name Element
 *  @description Extensions to the DOM Core <a href="http://www.w3.org/TR/DOM-Level-3-Core/core.html#ID-745549614"><code>Element</code></a> interface.
 *  @since TuneKit 1.0
 */

/* ==================== Element Extensions ==================== */

/**
 *  Indicates whether the element has a given class name within its <code>class</code> attribute.
 *
 *  @param {String} className The CSS class name.
 *  @returns {bool} Whether the element has this class name within its <code>class</code> attribute.
 *  @memberOf Element.prototype
 */
Element.prototype.hasClassName = function (className) {
  return new RegExp('(?:^|\\s+)' + className + '(?:\\s+|$)').test(this.className);
};

/**
 *  Adds the given class name to the element's <code>class</code> attribute if it's not already there.
 *
 *  @param {String} className The CSS class name.
 *  @memberOf Element.prototype
 */
Element.prototype.addClassName = function (className) {
  if (!this.hasClassName(className)) {
    this.className = [this.className, className].join(' ');
  }
};

/**
 *  Removes the given class name from the element's <code>class</code> attribute if it's there.
 *
 *  @param {String} className The CSS class name.
 *  @memberOf Element.prototype
 */
Element.prototype.removeClassName = function (className) {
  if (this.hasClassName(className)) {
    var curClasses = this.className;
    this.className = curClasses.replace(new RegExp('(?:^|\\s+)' + className + '(?:\\s+|$)', 'g'), ' ');
  }
};

/**
 *  Adds the given class name to the element's <code>class</code> attribute if it's not there, or removes it if it's already set.
 *
 *  @param {String} className The CSS class name.
 *  @memberOf Element.prototype
 */
Element.prototype.toggleClassName = function (className) {
  this[this.hasClassName(className) ? 'removeClassName' : 'addClassName'](className);
};

/**
 *  Removes all the children from an element.
 *
 *  @memberOf Element.prototype
 */
// XXX: should this be on Node?
Element.prototype.removeAllChildren = function () {
  while (this.firstChild) {
    this.removeChild(this.firstChild);
  }
};

/**
 *  Returns true if the element has the given child node
 *  FIXME: should this be on Node?
 *
 *  @param {Element} child The child to search for
 *  @memberOf Element.prototype
 */
Element.prototype.hasChild = function (child) {
  for (var i=0; i < this.childNodes.length; i++) {
    if (this.childNodes[i] === child) {
      return true;
    }
  }
  return false;
};

/**
 *  Applies a transition definition to the element, allowing the transition to be reversed. If this method is called
 *  within a {@link TKTransaction}, the transition will only be commited when the transaction is completed.
 *
 *  @param {TKTransitionDefinition} transitionDefinition The transition applied to the element.
 *  @param {bool} reversed Indicates whether the transition is to be applied in reverse.
 */
Element.prototype.applyTransition = function (definition, reversed) {
  // nothing to do if we have no definition
  if (definition === null) {
    return;
  }
  // create a TKTransition from the definition
  var transition = new TKTransition(definition);
  // this view will be the target
  transition.target = this;
  // revert from / to values as instructed
  if (reversed) {
    var from = transition.from;
    transition.from = transition.to;
    transition.to = from;
  }
  // set up base properties, if any
  if (definition.base) {
    for (var i = 0; i < definition.base.length; i += 2) {
      this.style.setProperty(definition.base[i], definition.base[i+1], '');
    }
  }
  // start the transition
  transition.start();
};

Element.prototype.getBounds = function () {
  return TKRect.rectFromClientRect(this.getBoundingClientRect());
};

Element.prototype.isNavigable = function () {
  var is_navigable = false;
  if (this._controller !== undefined && this._controller !== null && this._controller.navigableElements.indexOf(this) !== -1) {
    var style = window.getComputedStyle(this);
    is_navigable = (
      style.display != 'none' && style.visibility != 'hidden' &&
      !this.hasClassName(TKSpatialNavigationManagerInactiveCSSClass)
    );
  }
  return is_navigable;
};

TKUtils.setupDisplayNames(Element, 'Element');
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */
 
var TKEventTriage = {};

TKEventTriage.handleEvent = function (event) {
  // first call the super class method that we may be overriding otherwise
  if (this instanceof TKObject) {
    this.callSuper(event);
  }
  //
  var type = event.type;
  var methodName = 'handle' + type.charAt(0).toUpperCase() + type.substr(1);
  if (TKUtils.objectHasMethod(this, methodName)) {
    this[methodName](event);
  }
};

TKUtils.setupDisplayNames(TKEventTriage, 'TKEventTriage');
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */
 
/* ==================== Constants ==================== */

const TKObjectPropertyChanged = 'handlePropertyChange';

/* ==================== TKObject ==================== */

/**
 *  @class
 *
 *  <p>The TKObject class is the base class for all TuneKit objects and provides a way to receive and trigger
 *  notifications when a JavaScript property changes.</p>
 *
 *  <p>Observing a property on an object is done through the
 *  {@link #addPropertyObserver} method, specifying the property to observe as well as the object that will
 *  receive the notifications of the property change. Likewise, an object can stop observing such changes using
 *  the {@link #removePropertyObserver} method. When a property value changes, the author needs to call the 
 *  {@link #notifyPropertyChange} method so that registered observers will be notified. Note that synthetized
 *  properties will automatically trigger notifications when changed, so in this case, setters need not 
 *  manually call {@link #notifyPropertyChange}.</p>
 *
 *  <p>Finally, TKObject also provides the {@link #callSuper} method to call the superclass's implementation
 *  of an overload method.</p>
 *  
 *  @since TuneKit 1.0
 */
function TKObject () {
  this.observedProperties = {};
};

/* ==================== Method overriding ==================== */

/**
 *  This method calls the object's superclass implementation of the current method
 */
TKObject.prototype.callSuper = function () {
  // figure out what function called us
  var caller = TKObject.prototype.callSuper.caller;
  // if that function is a constructor, we call the parent class's constructor
  if (TKUtils.objectHasMethod(caller, 'inherits')) {
    caller.inherits.apply(this, arguments);
  }
  // otherwise we look at that function name in the parent prototype
  else {
    var parent = caller._class.inherits.prototype;
    var method_name = caller._name;
    if (TKUtils.objectHasMethod(parent, method_name)) {
      return parent[method_name].apply(this, arguments);
    }
  }
};

/* ==================== Observing ==================== */

/**
 *  Indicates whether this object has registered observers for this property
 *
 *  @param {String} propertyName The property that may be observed.
 *
 *  @returns {bool} Whether this object has registered observers for this property
 *  @private
 */
TKObject.prototype.isPropertyObserved = function (propertyName) {
  return !TKUtils.objectIsUndefined(this.observedProperties[propertyName]);
};

/**
 *  Adds an observer for the named property on this object. In case an existing
 *  combination of the observer and property is already registered, this method
 *  is a no-op.
 *
 *  @param {String} propertyName The property to observe.
 *  @param {Object} observer The object that will be notified when the property is changed.
 *  @param {String} methodName The optional method name that will be called on the observer when the property is changed. 
 *  If this property is not provided, the <code>observer</code> must implement the {@link TKPropertyValueChange} protocol.
 */
TKObject.prototype.addPropertyObserver = function (propertyName, observer, methodName) {
  // create the array for this property if it's not already there
  if (!this.isPropertyObserved(propertyName)) {
    this.observedProperties[propertyName] = new Array();
  }
  // do nothing if we already have this observer registered
  else if (this.observedProperties[propertyName].indexOf(observer) > -1) {
    return;
  }
  // now, add the observer to the observer array for this property if valid
  var methodName = methodName || TKObjectPropertyChanged;
  if (TKUtils.objectHasMethod(observer, methodName)) {
    this.observedProperties[propertyName].push({
      observer: observer,
      methodName : methodName
    });
  }
};

/**
 *  Removes the observer for the named property on this object. In case an existing
 *  combination of the observer and property is not already registered, this method
 *  is a no-op.
 *
 *  @param {String} propertyName The observed property.
 *  @param {Object} observer The object that was notified when the property changed.
 *
 *  @returns {bool} Whether an observer was removed
 */
TKObject.prototype.removePropertyObserver = function (propertyName, observer) {
  // do nothing if this property is not observed
  if (!this.isPropertyObserved(propertyName)) {
    return false;
  }
  // now get the observer's index in the array
  var observers = this.observedProperties[propertyName];
  var observer_index = observers.indexOf(observer);
  // remove the observer if it was registered
  if (observer_index > -1) {
    observers.splice(observer_index, 1);
  }
  // let the user know whether we succeeded
  return (observer_index > -1);
};

/**
 *  Triggers a notification that the given property on this object has changed.
 *  For synthesized properties, this is called automatically upon setting the
 *  property. For methods that update an instance variable that is not synthesized,
 *  {@link #notifyPropertyChange} has to be called manually so that observers are notified.
 *
 *  @param {String} propertyName The observed property.
 */
TKObject.prototype.notifyPropertyChange = function (propertyName) {
  // do nothing if this property is not observed
  if (!this.isPropertyObserved(propertyName)) {
    return;
  }
  // now, go through each observer for this property and notify them
  var observers = this.observedProperties[propertyName];
  for (var i = 0; i < observers.length; i++) {
    var observer = observers[i];
    observer.observer[observer.methodName](this, propertyName);
  }
};

/**
 *  Calls a method on this object after a delay, allowing any number of optional extra arguments to be
 *  passed after the first two mandatory ones.
 *
 *  @param {String} methodName The method name to be called.
 *  @param {int} delay The delay in miliseconds.
 *
 *  @returns {int} The timeout that can be used to call <code>clearTimeout</code>.
 */
TKObject.prototype.callMethodNameAfterDelay = function (methodName, delay) {
  var _this = this;
  var args = Array.prototype.slice.call(arguments, 2);
  var generated_function = function () {
    _this[methodName].apply(_this, args);
  };
  generated_function.displayName = TKUtils.createDisplayName(this.constructor.name, methodName);
  return setTimeout(generated_function, delay);
};

/**
 *  @class
 *  @name TKPropertyValueChange
 *  @since TuneKit 1.0
 */

/**
 *  Invoked when a property on an observed object has been changed.
 *
 *  @name handlePropertyChange
 *  @function
 *
 *  @param {Object} observedObject The observed object
 *  @param {String} propertyName The observed property's name as a string
 *  @memberOf TKPropertyValueChange.prototype
 */

TKClass(TKObject, 'TKObject');
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

/**
 *  @class
 *  @name TKTransitionDelegate
 *  @since TuneKit 1.0
 */

/**
 *  Invoked when a transition has completed.
 *
 *  @name transitionDidComplete
 *  @function
 *
 *  @param {TKTransition} theTransition The transition that just completed.
 *  @memberOf TKTransitionDelegate.prototype
 */

const TKTransitionDidCompleteDelegate = 'transitionDidComplete';

const TKTransitionDefaults = {
  duration  : 0.5,
  delay     : 0,
  removesTargetUponCompletion : false,
  revertsToOriginalValues : false
};

const TKTransitionStyles = ['-webkit-transition-property', '-webkit-transition-duration', '-webkit-transition-timing-function', '-webkit-transition-delay', '-webkit-transition'];

/* ==================== TKTransition ==================== */

/**
 *  @class
 *
 *  <p>The TKTransition class allows to create a synchronized change of one or more property values on a
 *  {@link Element} instance or any DOM element.</p>
 *
 *  <p>First, the user sets the {@link #target} for the transition,
 *  identifying the target element, and second the set of {@link #properties}, in the form of an <code>Array</code>
 *  of CSS properties for the element. Then the {@link #to} and optional
 *  {@link #from} value arrays are provided to define what values will be used for the transition. Each item in the
 *  {@link #from} and {@link #to} arrays matches the item at the same index in the {@link #properties} array, and the same
 *  applies to the {@link #duration} property, which can also be a single value shared for all transitioned properties.</p>
 *
 *  <p>Finally, once the properties on the transition are all set, the {@link #start} method must be called so that the
 *  transition is started. Note that it is possible to group transitions within a {@link TKTransaction} and set a default
 *  set of transition properties within a transaction using the {@link TKTransaction.defaults} static property.</p>
 *  
 *  <p>The following example shows how to make a transition that fades an element in as it animates from the right side of the screen:</p>
 *
<pre class="example">
new TKTransition({
  target : anElement,
  properties : ['opacity', '-webkit-transform'];
  from : [0, 'translate(320px, 0)'],
  to : [1, 'translate(0, 0)']
  duration : 0.5;
}).start();
</pre>
 *
 *  <p>Note that properties of a {@link TKTransition} object can be passed as a batch to the {@link TKTransition} constructor
 *  as an anonymous object. This also allows reuse of a set of parameters across several transitions. Also, a set of pre-baked
 *  transitions exist can be easily applied to an element with the {@link Element#applyTransition} method.</p>
 *
 *  @since TuneKit 1.0
 */
function TKTransition (params) {
  // set up defaults
  /**
   *  The transition target.
   *  @type Element 
   */
  this.target = null;
  /**
   *  The set of properties that will be transitioned. The properties are CSS properties of the targeted <code>Element</code>.
   *  @type Array 
   */
  this.properties = null;
  /**
   *  The set of durations in seconds, each duration matching a property in the {@link #properties} array.
   *  Note that it's possible to specify a single value instead of an array to use the same duration for 
   *  all properties.
   *  @type Object 
   */
  this.duration = null;
  /**
   *  The set of delays in seconds, each delay matching a property in the {@link #properties} array.
   *  Note that it's possible to specify a single delay instead of an array to use the same delay for 
   *  all properties.
   *  @type Object 
   */
  this.delay = null;
  /**
   *  Optional list of values to start the transition from. Each value in this array must match the property
   *  at the same index in the {@link #properties} array.
   *  @type Array
   */
  this.from = null;
  /**
   *  Required list of values to transition to. Each value in this array must match the property
   *  at the same index in the {@link #properties} array.
   *  @type Array
   */
  this.to = null;
  /**
   *  The set of timing functions, each timing function matching a property in the {@link #properties}
   *  array. Note that it's possible to specify a single timing function instead of an array to use the
   *  same timing function for all properties.
   *  @type Object 
   */
  this.timingFunction = null;
  /**
   *  The delegate object that implements the {@link TKTransitionDelegate} protocol.
   *  @type Object
   */
  this.delegate = null;
  /**
   *  Indicates whether the target needs to be removed once the transition completes. Defaults to <code>false</code>.
   *  @type bool
   */
  this.removesTargetUponCompletion = null;
  /**
   *  Indicates whether the target needs to reset the property that are transitioned to their original values
   *  once the transition completes. Defaults to <code>false</code>.
   *  @type bool
   */
  this.revertsToOriginalValues = null;
  //
  this.defaultsApplied = false;
  this.archivedStyles = null;
  this.archivedValues = [];
  // import params
  TKUtils.copyPropertiesFromSourceToTarget(params, this);
};

/* ==================== Dealing with defaults ==================== */

TKTransition.prototype.applyDefaults = function () {
  if (this.defaultsApplied) {
    return;
  }
  //
  for (var i in TKTransitionDefaults) {
    if (this[i] === null) {
      this[i] = TKTransitionDefaults[i];
    }
  }
  //
  this.defaultsApplied = true;
};

/* ==================== Archiving the transition styles ==================== */

TKTransition.prototype.getTargetStyle = function () {
  // if (this.target.style === null) {
  //   this.target.setAttribute('style', 'foo: bar');
  // }
  return this.target.style;
};

TKTransition.prototype.archiveTransitionStyles = function () {
  // do nothing if we already have archived styles in this run session
  if (this.archivedStyles !== null) {
    return;
  }
  // iterate all TKTransitionStyles and archive them
  this.archivedStyles = [];
  var style = this.getTargetStyle();
  for (var i = 0; i < TKTransitionStyles.length; i++) {
    this.archivedStyles.push(style.getPropertyValue(TKTransitionStyles[i]));
  }
};

TKTransition.prototype.restoreTransitionStyles = function () {
  var style = this.getTargetStyle();
  // iterate all TKTransitionStyles and restore them
  for (var i = 0; i < TKTransitionStyles.length; i++) {
    style.setProperty(TKTransitionStyles[i], this.archivedStyles[i], '');
  }
  // reset archived styles
  this.archivedStyles = null;
};

/* ==================== Archiving the base values ==================== */

TKTransition.prototype.archiveBaseValues = function () {
  // do nothing if we don't need to archive base values
  if (!this.revertsToOriginalValues) {
    return;
  }
  var style = this.getTargetStyle();
  for (var i = 0; i < this.properties.length; i++) {
    this.archivedValues.push(style.getPropertyValue(this.properties[i]));
  }
};

TKTransition.prototype.restoreBaseValues = function () {
  var style = this.getTargetStyle();
  for (var i = 0; i < this.properties.length; i++) {
    style.setProperty(this.properties[i], this.archivedValues[i], null);
  }
};

/* ==================== Starting the transition ==================== */

/**
 *  Starts the transition.
 */
TKTransition.prototype.start = function () {
  // if we have an active transaction, just add to it
  if (TKTransaction.openTransactions > 0) {
    TKTransaction.addTransition(this);
    return;
  }  
  // otherwise, we'll just get it going
  this.applyDefaults();
  if (this.from === null) {
    this.applyToState();
  }
  else {
    this.applyFromState();
    var _this = this;
    setTimeout(function () {
      _this.applyToState();
    }, 0);  
  }
};

/* ==================== Applying the "from" state ==================== */

TKTransition.prototype.applyFromState = function () {
  // do nothing if we have no "from" state specified
  if (this.from === null) {
    return;
  }
  //
  this.applyDefaults();
  this.archiveTransitionStyles();
  var style = this.getTargetStyle();
  style.webkitTransitionDuration = 0;
  for (var i = 0; i < this.properties.length; i++) {
    style.setProperty(this.properties[i], this.from[i], '');
  }
};

/* ==================== Applying the "to" state ==================== */

TKTransition.prototype.applyToState = function () {
  // first, make sure we have defaults applied if some
  // properties are not explicitely set on our transition
  this.applyDefaults();

  // and that we archive the transition styles to be reverted
  this.archiveTransitionStyles();

  // and that we archive the original values
  this.archiveBaseValues();
  
  // now compile the styles needed for this transition
  this.cssProperties = [];
  var transition_styles = [];
  for (var i = 0; i < this.properties.length; i++) {
    var property = this.properties[i];
    // do nothing if we already have an animation defined for this
    if (this.cssProperties.indexOf(property) > -1) {
      continue;
    }
    // else, set up the CSS style for this transition
    var duration = (TKUtils.objectIsArray(this.duration)) ? this.duration[i] : this.duration;
    var timing = (TKUtils.objectIsArray(this.timingFunction)) ? this.timingFunction[i] : this.timingFunction;
    var delay = (TKUtils.objectIsArray(this.delay)) ? this.delay[i] : this.delay;
    transition_styles.push([property, duration + 's', timing, delay + 's'].join(' '));
    // and remember we are animating this property
    this.cssProperties.push(property);
  }

  var style = this.getTargetStyle();
  for (var i = 0; i < this.properties.length; i++) {
    style.setProperty(this.properties[i], this.to[i], '');
  }

  // set up the transition styles
  style.webkitTransition = transition_styles.join(', ');

  // register for events to track transition completions
  this.target.addEventListener('webkitTransitionEnd', this, false);
  this.completedTransitions = 0;
};

/* ==================== Tracking transition completion ==================== */

// XXX: we won't be getting an event for properties that have the same value in the to
// state, so we'll need to do a little work to track css properties that won't really transition
TKTransition.prototype.handleEvent = function (event) {
  // do nothing if that event just bubbled from our target's sub-tree
  if (event.currentTarget !== this.target) {
    return;
  }

  // update the completion counter
  this.completedTransitions++;

  // do nothing if we still have running transitions
  if (this.completedTransitions != this.cssProperties.length) {
    return;
  }

  // the counter reached our properties count, fire up the delegate
  if (TKUtils.objectHasMethod(this.delegate, TKTransitionDidCompleteDelegate)) {
    this.delegate[TKTransitionDidCompleteDelegate](this);
  }

  // remove from the tree if instructed to do so
  if (this.removesTargetUponCompletion) {
    this.target.parentNode.removeChild(this.target);
  }
  // otherwise, restore transition styles
  else {
    this.restoreTransitionStyles();
  }
  
  // restore original values if instructed to do so
  if (this.revertsToOriginalValues) {
    this.restoreBaseValues();
  }
};

TKClass(TKTransition);
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

/* ==================== TKTransaction ==================== */

/**
 *  @class
 *
 *  <p>A transaction allows to run a variety of transitions in sync, no matter in what function or JavaScript run loop
 *  the transition itself was applied. Transactions can be nested, and a transaction is only truly commited when there
 *  are no other open transactions. In other words, there must be as many calls to {@link TKTransaction.begin} as there
 *  are calls to {@link TKTransaction.commit} before any transition in one of those transactions can be applied.
 *
 *  @since TuneKit 1.0
 */
var TKTransaction = {
  transitions : [],
  openTransactions : 0,
  /**
   *  The set of default properties that will be applied to any {@link TKTransition} until the next call to {@link TKTransaction.commit}.
   *  Any of the properties that can be applied to a {@link TKTransition} can be applied to this object.
   *  @type Object
   */
  defaults : {},
  defaultsStates : []
};

/**
 *  Begins a new transaction and makes it the current transaction.
 */
TKTransaction.begin = function () {
  // reset the group if we're starting fresh
  if (this.openTransactions == 0) {
    this.transitions = [];
    this.defaults = {};
  }
  // otherwise, archive the current state of defaults
  else {
    this.defaultsStates.push(this.defaults);
    // XXX: should we restore defaults here as well?
  }
  // increase the number of open transactions
  this.openTransactions++;
};

/**
 *  Add Transition
 *
 *  @private
 */
TKTransaction.addTransition = function (transition) {
  // first, apply the transaction defaults to the transitions
  for (var i in this.defaults) {
    if (transition[i] === null) {
      transition[i] = this.defaults[i];
    }
  }
  // and add the transition to our array
  this.transitions.push(transition);
};

/**
 *  Closes the current transaction.
 */
TKTransaction.commit = function () {
  // do nothing if we have no open transactions
  if (this.openTransactions == 0) {
    return;
  }
  // decrease the number of open transactions
  this.openTransactions--;
  // if we still have open transactions, just
  // restore the previous defaults state
  if (this.openTransactions != 0) {
    this.defaults = this.defaultsStates.pop();
    return;
  }
  // otherwise, it's time to shake and bake, we'll apply the
  // "from" states directly and the "to" states immediately
  // after in a new run loop so that the "from" styles have
  // been resolved first
  var transitions = this.transitions;
  for (var i = 0; i < transitions.length; i++) {
    transitions[i].applyFromState();
  }
  setTimeout(function () {
    for (var i = 0; i < transitions.length; i++) {
      transitions[i].applyToState();
    }
  }, 0);
};

TKUtils.setupDisplayNames(TKTransaction, 'TKTransaction');
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */
 
/**
 *  @class
 *
 *  A virtual class that allows the definition of pre-baked transitions that can be used as parameter
 *  for the {@link Element#applyTransition} method. In reality, any object that provides the type of
 *  properties instances of this class offers can be used with that method.
 *
 *  @name TKTransitionDefinition
 *  @since TuneKit 1.0
 */

/**
 *  @name TKTransitionDefinition.prototype
 *  @property {Array} base A set of property / value pairs that are applied to the element as the transition starts. The properties
 *  listed there are not supposed to be transitioned. If you wish to set a from state for a property that gets transitioned, use
 *  the {@link #properties} and {@link from} properties instead.
 *  @property {Array} properties The set of properties that will be transitioned. The properties are CSS properties
 *  of the element that will be transitioned using this definition.
 *  @property {Array} from Optional list of values to start the transition from. Each value in this array must match the property
 *  at the same index in the {@link #properties} array.
 *  @property {Array} to Required list of values to transition to. Each value in this array must match the property
 *  at the same index in the {@link #properties} array.
 */

/**
 *  Fades out.
 *  @constant
 *  @type TKTransitionDefinition
 */
const TKViewTransitionDissolveOut = {
  properties : ['opacity'],
  from : [1],
  to : [0]
};

/**
 *  Fades in.
 *  @constant
 *  @type TKTransitionDefinition
 */
const TKViewTransitionDissolveIn = {
  properties : ['opacity'],
  from : [0],
  to : [1]
};

/**
 *  Fades in while scaling up to identity scale.
 *  @constant
 *  @type TKTransitionDefinition
 */
const TKViewTransitionZoomIn = {
  properties : ['opacity', '-webkit-transform'],
  from : [0, 'scale(0.2)'],
  to : [1, 'scale(1)']
};

/**
 *  Fades out while scaling down to identity scale.
 *  @constant
 *  @type TKTransitionDefinition
 */
const TKViewTransitionZoomOut = {
  properties : ['opacity', '-webkit-transform'],
  from : [0, 'scale(1.2)'],
  to : [1, 'scale(1)']
};

/**
 *  Fades in while rotating from the right.
 *  @constant
 *  @type TKTransitionDefinition
 */
const TKViewTransitionCrossSpinRight = {
  properties : ['opacity', '-webkit-transform'],
  from : [0, 'rotate(20deg)'],
  to : [1, 'rotate(0)']
};

/**
 *  Fades in while rotating from the left.
 *  @constant
 *  @type TKTransitionDefinition
 */
const TKViewTransitionCrossSpinLeft = {
  properties : ['opacity', '-webkit-transform'],
  from : [0, 'rotate(-20deg)'],
  to : [1, 'rotate(0)']
};

/**
 *  Scale transition scaling in.
 *  @constant
 *  @type TKTransitionDefinition
 */
const TKViewTransitionScaleIn = {
  base : ['z-index', 1],
  properties : ['-webkit-transform'],
  from : ['scale(0.01)'],
  to : ['scale(1)']
};

/**
 *  Scale transition scaling out.
 *  @constant
 *  @type TKTransitionDefinition
 */
const TKViewTransitionScaleOut = {
  base : ['z-index', 1],
  properties : ['-webkit-transform'],
  from : ['scale(1)'],
  to : ['scale(0.01)']
};
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

/* ==================== Constants ==================== */

const TKAnimatorLinearType = 0;
const TKAnimatorSplinesType = 1;
const TKAnimatorInvalidArgsException = 2;

const TKAnimatorAnimationDidIterate = 'animationDidIterate';
const TKAnimatorAnimationDidEnd = 'animationDidEnd';

/* ==================== TKAnimator ==================== */

function TKAnimator (duration, delegate, spline) {
  // check validity of arguments number
  // if (arguments.length != 2 && arguments.length != 3 && arguments.length != 7) {  
  //   throw TKAnimatorInvalidArgsException;
  //   return false;
  // }
  // init some base properties
  this.ready = false;
  this.animating = false;
  this.timer = null;
  // handle arguments
  this.duration = duration; // ms
  this.delegate = delegate;
  // check we have the required delegation method
  // if (!TKUtils.objectHasMethod(this.delegate, TKAnimatorAnimationDidIterate)) {
  //   return;
  // }
  // handle splines arguments, if available
  if (arguments.length >= 3) {
    this.type = TKAnimatorSplinesType;
    this.x1 = spline[0];
    this.y1 = spline[1];
    this.x2 = spline[2];
    this.y2 = spline[3];
    this.init();
  }
  else { // linear animation
    this.type = TKAnimatorLinearType;
  }
  this.ready = true;
};

TKAnimator.prototype.init = function () {
  // calculate the polynomial coefficients
  this.cx = 3 * this.x1;
  this.bx = 3 * (this.x2 - this.x1) - this.cx;
  this.ax = 1 - this.cx - this.bx;
  this.cy = 3 * this.y1;
  this.by = 3 * (this.y2 - this.y1) - this.cy;
  this.ay = 1 - this.cy - this.by;
  // compute points
  var numberOfPoints = (this.duration / 1000) * 240;
  this.curve = new Array(numberOfPoints);
  var dt = 1.0 / ( numberOfPoints - 1 );
  for (var i = 0; i < numberOfPoints; i++) {
    var t = i * dt;
    this.curve[i] = {
      x : (this.ax * Math.pow(t, 3)) + (this.bx * Math.pow(t, 2)) + (this.cx * t),
      y : (this.ay * Math.pow(t, 3)) + (this.by * Math.pow(t, 2)) + (this.cy * t)
    };
  }
};

TKAnimator.prototype.start = function () {
  if (!this.ready) {
    var _this = this;
    this.timer = setTimeout(function () { _this.start() }, 0);
    return;
  }
  this.animating = true;
  this.lastIndex = 0;
  this.startTime = (new Date()).getTime();
  this.iterate();
};

TKAnimator.prototype.stop = function () {
  this.animating = false;
  clearTimeout(this.timer);
};

TKAnimator.prototype.iterate = function () {
  var ellapsedTime = (new Date()).getTime() - this.startTime;
  if (ellapsedTime < this.duration) {
    var x = ellapsedTime / this.duration;
    // handle splines case
    if (this.type == TKAnimatorSplinesType) {
      var y = 0;
      for (var i = this.lastIndex; i < this.curve.length; i++) {
        var point = this.curve[i];
        if (point.x >= x && i > 0) {
          var previous_point = this.curve[i - 1];
          if ((x - previous_point.x) < (point.x - x)) {
            this.lastIndex = i - 1;
            y = previous_point.y;
          }
          else {
            this.lastIndex = i;
            y = point.y;
          }
          break;
        }
      }
    }
    this.delegate[TKAnimatorAnimationDidIterate]((this.type == TKAnimatorSplinesType) ? y : x);
    var _this = this;
    this.timer = setTimeout(function () { _this.iterate() }, 0);
  }
  else {
    this.delegate[TKAnimatorAnimationDidIterate](1);
    if (TKUtils.objectHasMethod(this.delegate, TKAnimatorAnimationDidEnd)) {
      this.delegate[TKAnimatorAnimationDidEnd]();
    }
    this.animating = false;    
  }
};

/* ==================== CLASS CREATION ==================== */

TKClass(TKAnimator);
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

// ---------------------------------------------------
// A two dimensional sliding view
// ---------------------------------------------------

/**
 *  @class
 *  @name TKSlidingViewData
 *  @since TuneKit 1.0
 */

/**
 *  @name TKSlidingViewData.prototype
 *
 *  @property {int} sideElementsVisible The number of elements on each side of the selected page. If the {@link #incrementalLoading} property is set to
 *  <code>true</code>, this specifies the number of elements in the DOM on each side as others beyond that range are removed from the tree. Otherwise, this
 *  specifies the threshold after which elements in either direction from the selected page get the <code>sliding-view-element-hidden</code> CSS class applied.
 *
 *  @property {int} distanceBetweenElements The distance in pixels between the center points of each page, essentially the overall width of each page.
 *
 *  @property {int} sideOffsetBefore Any additional margin in pixels to the left of each page.
 *
 *  @property {int} sideOffsetAfter Any additional margin in pixels to the right of each page.
 *
 *  @property {Array} elements The elements for the sliding view.
 *
 *  @property {bool} incrementalLoading Indicates whether elements in the sliding view's DOM are added and removed gradually as we browse through it, or all
 *  available in one go, which is the default. If you are populating a sliding view with a large amount of content, you should consider setting this property
 *  to <code>true</code> in order to ease memory constraints and enhance performance.
 *
 *  @property {bool} loops Whether we loop through pages. Defaults to <code>false</code>.
 *
 */

// data source method names
const TKSlidingViewNumberOfElements = 'slidingViewNumberOfElements';
const TKSlidingViewElementAtIndex = 'slidingViewElementAtIndex';

// delegate method names
const TKSlidingViewStyleForItemAtIndex = 'slidingViewStyleForItemAtIndex';
const TKSlidingViewDidSelectActiveElement = 'slidingViewDidSelectActiveElement';
const TKSlidingViewDidFocusElementAtIndex = 'slidingViewDidFocusElementAtIndex';
const TKSlidingViewDidBlurElementAtIndex = 'slidingViewDidBlurElementAtIndex';
const TKSlidingViewDidHideElementAtIndex = 'slidingViewDidHideElementAtIndex'; // TODO: XXX
const TKSlidingViewWillUnhideElementAtIndex = 'slidingViewWillUnhideElementAtIndex'; // TODO: XXX

const TKSlidingViewDidHoverElementAtIndex = 'slidingViewDidHoverElementAtIndex';
const TKSlidingViewDidUnhoverElementAtIndex = 'slidingViewDidUnhoverElementAtIndex';

// css protocol
const TKSlidingViewCSSContainerClass = 'sliding-view';
const TKSlidingViewCSSElementClass = 'sliding-view-element';
const TKSlidingViewCSSFocusedClass = 'sliding-view-element-focused';
const TKSlidingViewCSSSideBeforeClass = 'sliding-view-element-before';
const TKSlidingViewCSSSideAfterClass = 'sliding-view-element-after';
const TKSlidingViewCSSStagedBeforeClass = 'sliding-view-element-staged-before';
const TKSlidingViewCSSStagedAfterClass = 'sliding-view-element-staged-after';
const TKSlidingViewCSSHiddenClass = 'sliding-view-element-hidden';

// orientations
const TKSlidingViewOrientationHorizontal = 'horizontal';
const TKSlidingViewOrientationVertical = 'vertical';

TKSlidingView.synthetizes = ['dataSource',
                             'delegate',
                             'activeElement',
                             'activeElementIndex', // the index of the middle/focused element
                             'orientation', // whether the view should be horizontal or vertical
                             'interactive', // whether or not this view will listen for mouse events
                             'sideOffsetBefore', // gap between focused element and the elements before it
                             'sideOffsetAfter', // gap between focused element and the elements after it
                             'distanceBetweenElements', // general distance between elements in the layout
                             'sideElementsVisible', // the number of elements that are considered visible before and after the focus
                             'pageControl', // a TKPageControl object that should be linked to this slider (not needed)
                             'incrementalLoading', // whether or not the elements should be added to the view as required
                             'loops', // if true, the sliding view loops continuously
                             'raiseHoverEvents', // if true, the sliding view will use the Hover and Unhover delegate methods
                             'numberOfElements'];

function TKSlidingView (element) {
  this.callSuper();
  // these defaults look ok for elements about 180 square
  this._activeElementIndex = 0;
  this._orientation = TKSlidingViewOrientationHorizontal;
  this._interactive = true;
  this._sideOffsetBefore = 160;
  this._sideOffsetAfter = 160;
  this._distanceBetweenElements = 25;
  this._sideElementsVisible = 4;
  this._pageControl = null;
  this._incrementalLoading = false;
  this._loops = false;
  this._raiseHoverEvents = false;
  
  this._elements = [];
  
  if (element) {
    this.element = element;
  } else {
    // create the element we'll use as a container
    this.element = document.createElement("div");
  }
  this.element.addClassName(TKSlidingViewCSSContainerClass);
}

TKSlidingView.prototype.init = function () {

  if (!this.dataSource ||
      !TKUtils.objectHasMethod(this.dataSource, TKSlidingViewNumberOfElements) ||
      !TKUtils.objectHasMethod(this.dataSource, TKSlidingViewElementAtIndex)) {
    return;
  }

  var numElements = this.numberOfElements;

  if (this._incrementalLoading) {
    // add enough to be visible
    this.bufferElements();
  } else {
    // add all the elements
    for (var i=0; i < numElements; i++) {
      var el = this.dataSource[TKSlidingViewElementAtIndex](this, i);
      el.addClassName(TKSlidingViewCSSElementClass);
      el._needsAppending = true;
      this._elements[i] = el;
      el._slidingViewIndex = i;
      if (this._interactive) {
        el.addEventListener("click", this, false);
      }
      if (this._raiseHoverEvents) {
        el.addEventListener("mouseover", this, false);
        el.addEventListener("mouseout", this, false);
      }
    }
  }
  
  this.layout(true);
};

TKSlidingView.prototype.setPageControl = function (newPageControl) {
  this._pageControl = newPageControl;
  this._pageControl.deferCurrentPageDisplay = true;
  this._pageControl.delegate = this;
  this._pageControl.currentPage = this._activeElementIndex;
};

TKSlidingView.prototype.getActiveElement = function () {
  return this._elements[this._activeElementIndex];
};

TKSlidingView.prototype.setActiveElementIndex = function (newActiveElementIndex) {
  
  if ((this._loops || (newActiveElementIndex >= 0 && newActiveElementIndex < this.numberOfElements)) &&
      newActiveElementIndex != this._activeElementIndex) {

    var needsForcedLayout = (this._activeElementIndex === undefined);

    // call delegate to inform blur of current active element
    if (!needsForcedLayout && TKUtils.objectHasMethod(this.delegate, TKSlidingViewDidBlurElementAtIndex)) {
      this.delegate[TKSlidingViewDidBlurElementAtIndex](this, this._activeElementIndex);
    }

    if (newActiveElementIndex < 0) {
      this._activeElementIndex = (this.numberOfElements + newActiveElementIndex) % this.numberOfElements;
    } else {
      this._activeElementIndex = newActiveElementIndex % this.numberOfElements;
    }

    // if there is a page control, tell it to update
    if (this._pageControl) {
      this._pageControl.currentPage = newActiveElementIndex;
    }
    
    this.bufferElements();
    this.layout(needsForcedLayout);

    // call delegate to inform focus of new active element
    // this needs to be done at the very end so we're use any code depending on
    // .activeElement actually works since we need elements buffered
    if (TKUtils.objectHasMethod(this.delegate, TKSlidingViewDidFocusElementAtIndex)) {
      this.delegate[TKSlidingViewDidFocusElementAtIndex](this, this._activeElementIndex);
    }
  }
};

TKSlidingView.prototype.getNumberOfElements = function () {
  if (this.dataSource) {
    return this.dataSource[TKSlidingViewNumberOfElements](this);
  } else {
    return 0;
  }
};

TKSlidingView.prototype.getElementAtIndex = function (index) {
  return this._elements[index];
};

// this method loads the elements that are necessary for
// display, and removes the ones that are not needed
TKSlidingView.prototype.bufferElements = function () {
  if (this._incrementalLoading) {
    var numElements = this.numberOfElements;
    for (var i=0; i < numElements; i++) {
      var offset = this._activeElementIndex - i;
      var absOffset = Math.abs(offset);
      if (this._loops) {
        // FIXME: check this! doesn't seem right
        var offset2 = offset + ((offset < 0) ? numElements : -numElements);
        var absOffset2 = Math.abs(offset2);
        if (absOffset2 <= this._sideElementsVisible) {
          offset = offset2;
          absOffset = absOffset2;
        }
      }
      if (absOffset <= this._sideElementsVisible) {
        if (!this._elements[i]) {
          var el = this.dataSource[TKSlidingViewElementAtIndex](this, i);
          el.addClassName(TKSlidingViewCSSElementClass);
          el._needsAppending = true;
          this._elements[i] = el;
          el._slidingViewIndex = i;
          if (this._interactive) {
            el.addEventListener("click", this, false);
          }
          if (this._raiseHoverEvents) {
            el.addEventListener("mouseover", this, false);
            el.addEventListener("mouseout", this, false);
          }
          
        }
      } else {
        // element isn't needed
        if (this._elements[i]) {
          this.element.removeChild(this._elements[i]);
          this._elements[i] = null;
        }
      }
    }
  }
};

TKSlidingView.prototype.layout = function (forceLayout) {
  var numElements = this.numberOfElements;

  for (var i=0; i < numElements; i++) {
    var offset = this._activeElementIndex - i;
    var absOffset = Math.abs(offset);
    if (this._loops) {
      // FIXME: check this! doesn't seem right
      var offset2 = offset + ((offset < 0) ? numElements : -numElements);
      var absOffset2 = Math.abs(offset2);
      if (absOffset2 <= this._sideElementsVisible) {
        offset = offset2;
        absOffset = absOffset2;
      }
    }

    var element = this._elements[i];

    if (!element) {
      // only layout elements we need to
      continue;
    }

    // loaded elements might not yet have been added to the document
    // this makes them appear in the right place
    if (element._needsAppending) {
      this.element.appendChild(element);
      element._needsAppending = false;
    }

    // Three cases for layout:
    //    - element is inside (visible)
    //    - element is just outside (one element outside each edge - called "staged")
    //    - element is really outside (we call this "hidden" and inform delegate)

    var transform = null;
    if (absOffset <= this._sideElementsVisible) {
      if (offset > 0) {
        if (this._orientation == TKSlidingViewOrientationHorizontal) {
          transform = "translate3d(" + (-1 * (absOffset * this._distanceBetweenElements + this._sideOffsetBefore)) + "px, 0, 0)";
        } else {
          transform = "translate3d(0, " + (-1 * (absOffset * this._distanceBetweenElements + this._sideOffsetBefore)) + "px, 0)";
        }
        this.applySlidingClass(element, TKSlidingViewCSSSideBeforeClass);
      } else if (offset < 0) {
        if (this._orientation == TKSlidingViewOrientationHorizontal) {
          transform = "translate3d(" + (absOffset * this._distanceBetweenElements + this._sideOffsetAfter) + "px, 0, 0)";
        } else {
          transform = "translate3d(0, " + (absOffset * this._distanceBetweenElements + this._sideOffsetAfter) + "px, 0)";
        }
        this.applySlidingClass(element, TKSlidingViewCSSSideAfterClass);
      } else {
        transform = "translate3d(0, 0, 0)";
        this.applySlidingClass(element, TKSlidingViewCSSFocusedClass);
      }
      element.style.webkitTransform = transform;
      element.style.opacity = 1;
    } else if (absOffset == (this._sideElementsVisible + 1)) {
      // FIXME: this is wrong!! should be staged classes - worried this will break things if I fix it
      if (offset > 0) {
        if (this._orientation == TKSlidingViewOrientationHorizontal) {
          transform = "translate3d(" + (-1 * (absOffset * this._distanceBetweenElements + this._sideOffsetBefore)) + "px, 0, 0)";
        } else {
          transform = "translate3d(0, " + (-1 * (absOffset * this._distanceBetweenElements + this._sideOffsetBefore)) + "px, 0)";
        }
        this.applySlidingClass(element, TKSlidingViewCSSSideBeforeClass);
      } else {
        if (this._orientation == TKSlidingViewOrientationHorizontal) {
          transform = "translate3d(" + (absOffset * this._distanceBetweenElements + this._sideOffsetAfter) + "px, 0, 0)";
        } else {
          transform = "translate3d(0, " + (absOffset * this._distanceBetweenElements + this._sideOffsetAfter) + "px, 0)";
        }
        this.applySlidingClass(element, TKSlidingViewCSSSideAfterClass);
      }
      element.style.webkitTransform = transform;
      element.style.opacity = 0;
    } else if (absOffset > this._sideElementsVisible || forceLayout) {
      if (offset > 0) {
        if (this._orientation == TKSlidingViewOrientationHorizontal) {
          transform = "translate3d(" + (-1 * (absOffset * this._distanceBetweenElements + this._sideOffsetBefore)) + "px, 0, 0)";
        } else {
          transform = "translate3d(0, " + (-1 * (absOffset * this._distanceBetweenElements + this._sideOffsetBefore)) + "px, 0)";
        }
      } else {
        if (this._orientation == TKSlidingViewOrientationHorizontal) {
          transform = "translate3d(" + (absOffset * this._distanceBetweenElements + this._sideOffsetAfter) + "px, 0, 0)";
        } else {
          transform = "translate3d(0, " + (absOffset * this._distanceBetweenElements + this._sideOffsetAfter) + "px, 0)";
        }
      }
      this.applySlidingClass(element, TKSlidingViewCSSHiddenClass);
      element.style.webkitTransform = transform;
      element.style.opacity = 0;
    }
    // now see if we have any over-ride styles to apply from the delegate
    if (TKUtils.objectHasMethod(this.delegate, TKSlidingViewStyleForItemAtIndex)) {
      override_styles = this.delegate[TKSlidingViewStyleForItemAtIndex](this, i);
      for (var j = 0; j < override_styles.length; j++) {
        var override_style = override_styles[j];
        element.style.setProperty(override_style[0], override_style[1], '');
      }
    }
  }
};

TKSlidingView.prototype.applySlidingClass = function (element, className) {
  element.removeClassName(TKSlidingViewCSSFocusedClass);
  element.removeClassName(TKSlidingViewCSSSideBeforeClass);
  element.removeClassName(TKSlidingViewCSSSideAfterClass);
  element.removeClassName(TKSlidingViewCSSStagedBeforeClass);
  element.removeClassName(TKSlidingViewCSSStagedAfterClass);
  element.removeClassName(TKSlidingViewCSSHiddenClass);
  
  element.addClassName(className);
};

TKSlidingView.prototype.handleEvent = function (event) {
  switch (event.type) {
    case "click":
      this.handleClick(event);
      break;
    case "mouseover":
      this.handleMouseover(event);
      break;
    case "mouseout":
      this.handleMouseout(event);
      break;
    default:
      debug("unhandled event type in TKSlidingView: " + event.type);
  }
};

TKSlidingView.prototype.handleClick = function (event) {
  // The event.target should have an _slidingViewIndex property. If
  // not, then go up to parent
  var target = event.target;
  while (target && TKUtils.objectIsUndefined(target._slidingViewIndex)) {
    target = target.parentNode;
  }
  if (!target) {
    return;
  }
  
  if (target._slidingViewIndex == this.activeElementIndex) {
    if (TKUtils.objectHasMethod(this.delegate, TKSlidingViewDidSelectActiveElement)) {
      this.delegate[TKSlidingViewDidSelectActiveElement](this, this._activeElementIndex);
    }
  } else {
    // Check if the click was before or after the focused element.
    if (target._slidingViewIndex < this.activeElementIndex) {
      if (this._loops && target._slidingViewIndex == 0) {
        this.activeElementIndex = 0;
      } else {
        this.activeElementIndex--;
      }
    } else {
      if (this._loops && target._slidingViewIndex == this.numberOfElements - 1) {
        this.activeElementIndex = this.numberOfElements - 1;
      } else {
        this.activeElementIndex++;
      }
    }
  }
};

TKSlidingView.prototype.handleMouseover = function (event) {
  // The event.target should have an _slidingViewIndex property. If
  // not, then go up to parent
  var target = event.target;
  while (target && TKUtils.objectIsUndefined(target._slidingViewIndex)) {
    target = target.parentNode;
  }
  if (!target) {
    return;
  }
  
  if (TKUtils.objectHasMethod(this.delegate, TKSlidingViewDidHoverElementAtIndex)) {
    this.delegate[TKSlidingViewDidHoverElementAtIndex](this, target._slidingViewIndex);
  }
};

TKSlidingView.prototype.handleMouseout = function (event) {
  // The event.target should have an _slidingViewIndex property. If
  // not, then go up to parent
  var target = event.target;
  while (target && TKUtils.objectIsUndefined(target._slidingViewIndex)) {
    target = target.parentNode;
  }
  if (!target) {
    return;
  }
  
  if (TKUtils.objectHasMethod(this.delegate, TKSlidingViewDidUnhoverElementAtIndex)) {
    this.delegate[TKSlidingViewDidUnhoverElementAtIndex](this, target._slidingViewIndex);
  }
};

// delegate for page control
TKSlidingView.prototype.pageControlDidUpdateCurrentPage = function (control, newPageIndex) {
  if (control === this._pageControl) {
    this.activeElementIndex = newPageIndex;
    this._pageControl.updateCurrentPageDisplay();
  }
};


TKClass(TKSlidingView);

/* ====================== Datasource helper ====================== */

function TKSlidingViewDataSourceHelper(data, incrementalLoading) {
  this.data = data;
  this.incrementalLoading = incrementalLoading;
  this.elements = [];
};

TKSlidingViewDataSourceHelper.prototype.slidingViewNumberOfElements = function(view) {
  if (this.data) {
    return this.data.length;
  } else {
    return 0;
  }
};

TKSlidingViewDataSourceHelper.prototype.slidingViewElementAtIndex = function(view, index) {
  if (!this.data || index >= this.data.length) {
    return null;
  }
  var element = this.elements[index];
  if (!element) {
    var source = this.data[index];
    element = TKUtils.buildElement(source);
  }
  if (!this.incrementalLoading) {
    this.elements[index] = element;
  }
  return element;
};

/* ====================== Declarative helper ====================== */

TKSlidingView.buildSlidingView = function(element, data) {
  if (TKUtils.objectIsUndefined(data) || !data || data.type != "TKSlidingView") {
    return null;
  }

  var slidingView = new TKSlidingView(element);
  if (!TKUtils.objectIsUndefined(data.elements)) {
    slidingView.dataSource = new TKSlidingViewDataSourceHelper(data.elements, data.incrementalLoading);
  }

  TKSlidingView.synthetizes.forEach(function(prop) {
    if (prop != "dataSource" && prop != "delegate") {
      if (!TKUtils.objectIsUndefined(data[prop])) {
        slidingView[prop] = data[prop];
      }
    }
  });

  return slidingView;
};

/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

// ---------------------------------------------------
// A page control implementation
// ---------------------------------------------------

/**
 *  @class
 *  @name TKPageControlData
 *  @since TuneKit 1.0
 */

/**
 *  @name TKPageControlData.prototype
 *
 *  @property {int} distanceBetweenPageIndicators The distance in pixels between the center points of each indicator, essentially the overall
 *  width of each indicator.
 *
 *  @property {bool} showPageElements Indicates whether individual elements for each page should be shown, or only the pill. Defaults to <code>false</code.
 *
 *  @property {Element} indicatorElement The element to be used for the active element indicator.
 *
 *  @property {Element} pageElement The template element to be used to represent each of the pages.
 *
 *  @property {bool} incrementalJumpsOnly Indicates whether only interactive jumps of one page at a time are allowed.
 *
 *  @property {bool} allowsDragging Indicates whether dragging is allowed.
 *
 */

// data source method names
const TKPageControlIndicatorElement = 'pageControlIndicatorElement';
const TKPageControlPageElement = 'pageControlPageElement';

// delegate method names
const TKPageControlDidUpdateCurrentPage = 'pageControlDidUpdateCurrentPage';

// css protocol
const TKPageControlCSSClass = 'page-control';
const TKPageControlCSSIndicatorElementClass = 'page-control-indicator-element';
const TKPageControlCSSPageElementClass = 'page-control-page-element';

// TODO: orientations

TKPageControl.synthetizes = ['dataSource',
                             'delegate',
                             'interactive', // whether or not this view will listen for mouse events
                             'currentPage', // the index of the current page
                             'numPages', // the number of pages
                             'distanceBetweenPageIndicators', // the distance between the page ticks - FIXME: this is the wrong term
                             'showPageElements', // whether or not to show the page indicators
                             'incrementalJumpsOnly', // if true, the page control only allows interactive jumps of one page at a time
                             'allowsDragging', // if true, the pages control allows dragging
							 'uniqueClass', // adds a unique class name to each page indicator element
                             'deferCurrentPageDisplay']; // whether or not to update the display as soon as currentPage changes - needed for syncing with an external control when interactive

function TKPageControl (element) {
  this.callSuper();
  //
  this._interactive = true;
  this._currentPage = 0;
  this._numPages = 1;
  this._distanceBetweenPageIndicators = 50;
  this._showPageElements = true;
  this._incrementalJumpsOnly = true;
  this._allowsDragging = false;
  this._deferCurrentPageDisplay = false;
	this._uniqueClass = false;
  
  if (element) {
    this.element = element;
  } else {
    // create the element we'll use as a container
    this.element = document.createElement("div");
  }
  this.element.addClassName(TKPageControlCSSClass);
}

TKPageControl.prototype.init = function () {

  if (!this.dataSource ||
      !TKUtils.objectHasMethod(this.dataSource, TKPageControlIndicatorElement) ||
      (this._showPageElements && !TKUtils.objectHasMethod(this.dataSource, TKPageControlPageElement))) {
    return;
  }

  // add page elements if needed
  if (this.showPageElements) {
    // get the page element
    var pageElement = this.dataSource[TKPageControlPageElement](this);
    for (var i=0; i < this._numPages; i++) {
      var el = pageElement.cloneNode();
      el.addClassName(TKPageControlCSSPageElementClass);
		if(this._uniqueClass) el.addClassName('thumb-'+i);
      el.style.webkitTransform = "translate(" + (i * this._distanceBetweenPageIndicators) + "px, 0px)";
      el._pageControlIndex = i;
      this.element.appendChild(el);
    }
  }
  
  // add indicator element
  var indicatorElement = this.dataSource[TKPageControlIndicatorElement](this);
  indicatorElement.addClassName(TKPageControlCSSIndicatorElementClass);
  indicatorElement.style.webkitTransform = "translate(" + (this._currentPage * this._distanceBetweenPageIndicators) + "px, 0px)";
  this.element.appendChild(indicatorElement);
  
  if (this._interactive) {
    if (this._allowsDragging) {
      this.element.addEventListener("mousedown", this, false);
    } else {
      this.element.addEventListener("click", this, false);
    }
  }
};

TKPageControl.prototype.setCurrentPage = function (newCurrentPage) {
  if (this._currentPage == newCurrentPage ||
      newCurrentPage < 0 ||
      newCurrentPage >= this._numPages) {
    return;
  }
  
  this._currentPage = newCurrentPage;
  
  if (TKUtils.objectHasMethod(this.delegate, TKPageControlDidUpdateCurrentPage)) {
    this.delegate[TKPageControlDidUpdateCurrentPage](this, this._currentPage);
  }
  
  if (!this._deferCurrentPageDisplay) {
    this.updateCurrentPageDisplay();
  }
};

TKPageControl.prototype.updateCurrentPageDisplay = function () {
  var indicatorElement = this.dataSource[TKPageControlIndicatorElement](this);
  indicatorElement.style.webkitTransform = "translate(" + (this._currentPage * this._distanceBetweenPageIndicators) + "px, 0px)";
};

TKPageControl.prototype.handleEvent = function (event) {
  switch (event.type) {
    case "mousedown":
      this.handleDragBegan(event);
      break;
    case "mousemove":
      this.handleDragMove(event);
      break;
    case "mouseup":
      this.handleDragEnded(event);
      break;
    case "click":
      this.handleClick(event);
      break;
    default:
      debug("unhandled event type in TKPageControl: " + event.type);
  }
};

TKPageControl.prototype.setupMouseInteraction = function () {
  // in case we have page elements, let's look at the position of the first element as
  // the minimum x value that we'll use for interactions from then on
  if (this._showPageElements) {
    // get the elements
    var page_elements = this.element.querySelectorAll('.' + TKPageControlCSSPageElementClass);
    var page_element_bounds = page_elements[0].getBounds();
    this.minX = page_element_bounds.x + (page_element_bounds.width - this._distanceBetweenPageIndicators) / 2;
  }
  // otherwise, use the bounds of the container
  else {
    this.minX = this.element.getBounds().x;
  }
  // now convert this value into the coordinate system of our element
  var point = window.webkitConvertPointFromPageToNode(this.element, new WebKitPoint(this.minX, 0));
  this.minX = point.x;
};

TKPageControl.prototype.pageIndexAtXY = function (x, y) {
  var point = window.webkitConvertPointFromPageToNode(this.element, new WebKitPoint(x, y));
  var page_index = Math.floor((point.x - this.minX) / this._distanceBetweenPageIndicators);
  return Math.max(Math.min(page_index, this._numPages), 0);
};

TKPageControl.prototype.handleClick = function (event) {
  // set up the mouse interaction
  this.setupMouseInteraction();
  // mark that we are interacting
  // XXX: should we really be doing this? This class is not being removed it seems.
  this.element.addClassName("interactive");
  // set the current page based on that right from the get go
  this.currentPage = this.pageIndexAtXY(event.clientX, event.clientY);
};

TKPageControl.prototype.handleDragBegan = function (event) {
  if (!this._allowsDragging) {
    return;
  }
  // ensure we cancel the default web page behavior for a dragging interaction
  event.preventDefault();
  // set up the mouse interaction
  this.setupMouseInteraction();
  // mark that we are interacting
  this.element.addClassName("interactive");
  // set the current page based on that right from the get go
  this.currentPage = this.pageIndexAtXY(event.clientX, event.clientY);
  // track mouse moves
  window.addEventListener("mousemove", this, false);
  window.addEventListener("mouseup", this, false);
};

TKPageControl.prototype.handleDragMove = function (event) {
  // ensure we cancel the default web page behavior for a dragging interaction
  event.preventDefault();
  // update the page
  this.currentPage = this.pageIndexAtXY(event.clientX, event.clientY);
};

TKPageControl.prototype.handleDragEnded = function (event) {
  // ensure we cancel the default web page behavior for a dragging interaction
  event.preventDefault();
  // mark that we are not interacting anymore
  this.element.removeClassName("interactive");
  // stop tracking events
  window.removeEventListener("mousemove", this);
  window.removeEventListener("mouseup", this);
};

TKClass(TKPageControl);

/* ====================== Datasource helper ====================== */

function TKPageControlDataSourceHelper(data) {
  this.data = data;
  this.pageElement = null;
  this.indicatorElement = null;
};

TKPageControlDataSourceHelper.prototype.pageControlPageElement = function(pageControl) {
  if (!this.data) {
    return null;
  }
  if (!this.pageElement) {
    this.pageElement = TKUtils.buildElement(this.data.pageElement);
  }
  return this.pageElement;
};

TKPageControlDataSourceHelper.prototype.pageControlIndicatorElement = function(pageControl) {
  if (!this.data) {
    return null;
  }
  if (!this.indicatorElement) {
    this.indicatorElement = TKUtils.buildElement(this.data.indicatorElement);
  }
  return this.indicatorElement;
};

/* ====================== Declarative helper ====================== */

TKPageControl.buildPageControl = function(element, data) {
  if (TKUtils.objectIsUndefined(data) || !data || data.type != "TKPageControl") {
    return null;
  }

  var pageControl = new TKPageControl(element);

  pageControl.dataSource = new TKPageControlDataSourceHelper(data);

  TKPageControl.synthetizes.forEach(function(prop) {
    if (prop != "dataSource" && prop != "delegate") {
      if (!TKUtils.objectIsUndefined(data[prop])) {
        pageControl[prop] = data[prop];
      }
    }
  });

  return pageControl;
};

/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */
 
TKController.inherits = TKObject;
TKController.synthetizes = ['view', 'navigableElements', 'actions', 'outlets', 'scrollable', 'backButton', 'navigatesTo'];

/**
 *  The hash in which we keep references to all controller instantiated throughout the lifecycle of the booklet. Use a controller's {@link #id} to
 *  access the controller for that id.
 *  @type Object
 */
TKController.controllers = {};

/**
 *  The fraction of the scrollable element's width or height that is being scrolled by in order to increment or decrement the scroll offset.
 *  @constant
 *  @type float
 *  @private
 */
const TKControllerScrollIncrementFraction = 0.75;
/**
 *  The time in miliseconds that the scrolling animation lasts.
 *  @constant
 *  @type int
 *  @private
 */
const TKControllerScrollDuration = 500;
/**
 *  The spline used for the scrolling animation.
 *  @constant
 *  @type Array
 *  @private
 */
const TKControllerScrollSpline = [0.211196, 0.811224, 0.641221, 0.979592];
const TKControllerScrollDirectionUp = 0;
const TKControllerScrollDirectionDown = 1;
const TKControllerScrollDirectionLeft = 0;
const TKControllerScrollDirectionRight = 1;

/**
 *  @class
 *
 *  <p>The TKController class is the base class for all TuneKit controllers. Controllers are useful objects that control all the core functionalities of
 *  a screen or sub-screen: view-loading, interaction, navigation, etc.</p>
 *
 *  @extends TKObject
 *  @since TuneKit 1.0
 *
 *  @param {Object} data A hash of properties to use as this object is initialized.
 */
function TKController (data) {
  this.callSuper();
  //
  this.propertiesToRestoreOnLoad = [];
  // synthetized property
  this._view = null;
  /**
   *  @name TKController.prototype
   *  @property {Array} navigableElements The complete list of all elements that can be navigated to within this controller and all of its sub-controllers.
   *  The contents of this array should not be directly manipulated, instead use the {@link #addNavigableElement} and {@link #removeNavigableElement} methods.
   */
  this._navigableElements = [];
  /**
   *  The controller directly containing this controller instance, <code>null</code> if the controller is not attached to any yet.
   *  @type TKController
   */
  this.parentController = null;
  // default transition styles for navigation
  this.enforcesCustomTransitions = false; // whether we should use the custom transitions on ATV only
  /**
   *  The animated transition to use for this controller's view when the controller becomes inactive.
   *  @type TKTransitionDefinition
   */
  this.becomesInactiveTransition = TKViewTransitionDissolveOut;
  /**
   *  The animated transition to use for this controller's view when the controller becomes active.
   *  @type TKTransitionDefinition
   */
  this.becomesActiveTransition = TKViewTransitionDissolveIn;
  // default properties
  /**
   *  The unique id for this controller's view. This is the same string that will be used for the {@link #view}'s HTML <code>id</code> attribute, as well
   *  as a key in the {@link TKController.controllers} hash, and thus must be adequate for both uses. The controller's id is used in the view-loading mechanism,
   *  such that if there is an HTML file in the booklet's <code>views/</code> directory that shares the same name, it is that file that is loaded to provide
   *  the view's content.
   *  @type String
   */
  this.id = data.id;
  /**
   *  A DOM element to be used as the view for this controller, which overrides the default view-loading mechanism in case it's set before the view is loaded.
   *  @type Element
   *  @private
   */
  this.explicitView = null;
  /**
   *  The name of the template to be used to create the view's content. If there is an HTML file in the <code>templates/</code> directory with that name, the
   *  view is loaded by cloning the content of that file and replacing the ID with that provided by the {@link #id} property.
   *  @type String
   */
  this.template = null;
  /**
   *  A list of image URIs to preload.
   *  @type Array
   */
  this.preloads = [];
  this._navigatesTo = null;
  this._actions = null;
  this._outlets = null;
  this._scrollable = null;
  this._backButton = null;
  /**
   *  The highlighted element within that controller. This is only unique to the view managed by this controller, and not to the entire booklet or even any
   *  controllers that might be contained within this controller.
   *  @type Element
   *  @private
   */
  this.highlightedElement = null;
  /**
   *  Indicates that the view has not appeared on screen yet.
   *  @type bool
   *  @private
   */
  this.viewNeverAppeared = true;
  /**
   *  Indicates that the view was fully processed.
   *  @type bool
   *  @private
   */
  this.viewWasProcessed = false;
  /**
   *  The CSS selector for the default scrollable element. If this value is non-<code>null</code> then the up and down keys scroll the element specified
   *  by the selector.
   *  @type String
   */
  this.scrollableElement = null;
  /**
   *  The animator managing the currently scrolling element.
   *  @type TKAnimator
   *  @private
   */
  this.animator = new TKAnimator(TKControllerScrollDuration, null, TKControllerScrollSpline);
  this.upScrollData = {
    direction: TKControllerScrollDirectionUp,
    animator: this.animator
  }
  this.downScrollData = {
    direction: TKControllerScrollDirectionDown,
    animator: this.animator
  }
  // copy properties
  this.copyNonSynthetizedProperties(data);
  // register controller
  TKController.controllers[this.id] = this;
};

/**
 *  A utility method to get the controller from an Object that is either the {@link TKController#id} of a controller or a controller directly.
 *
 *  @param {Object} stringOrControllerReference Either the {@link TKController#id} of a controller or a controller directly
 *  @returns {TKController} The controller.
 */
TKController.resolveController = function (stringOrControllerReference) {
  return (TKUtils.objectIsString(stringOrControllerReference)) ? TKController.controllers[stringOrControllerReference] : stringOrControllerReference;
};

/**
 *  A utility method to copy all properties from another object onto the controller, ignoring any property that is synthetized.
 *
 *  @param {Object} properties An object containing a set of properties to be copied across to the receiver.
 *  @private
 */
TKController.prototype.copyNonSynthetizedProperties = function (properties) {
  for (var property in properties) {
    // don't copy synthetized properties but track them for later
    if (this.__lookupSetter__(property)) {
      this.propertiesToRestoreOnLoad[property] = properties[property];
      continue;
    }
    this[property] = properties[property];
  }
};

/* ==================== Managing the View ==================== */

TKController.prototype.getView = function () {
  // create the view if it's not set yet
  if (this._view === null) {
    this.loadView();
  }
  return this._view;
};

TKController.prototype.setView = function (view) {
  this.explicitView = view;
};

TKController.prototype.loadView = function () {
  this.viewNeverAppeared = false;
  // first, check if we have an element already defined
  var view;
  if (this.explicitView !== null) {
    view = this.explicitView;
    // check if node is already in the document
    this.viewNeverAppeared = !TKUtils.isNodeChildOfOtherNode(view, document);
  }
  // check if our view already exists in the DOM
  else {
    view = document.getElementById(this.id);
  }
  // if not, load it from the views directory
  if (view === null) {
    this.viewNeverAppeared = true;
    view = this.loadFragment('views', this.id);
    // there was no such view available, try and see if we have a template available
    if (view === null) {
      if (this.template !== null) {
        view = this.loadFragment('templates', this.template);
      }
      // no template, just create an empty <div> then
      if (view === null) {
        view = document.createElement('div');
      }
    }
  }
  // make sure we know when the view is added to the document if it
  // wasn't part of the DOM already
  if (this.viewNeverAppeared) {
    view.addEventListener('DOMNodeInsertedIntoDocument', this, false);
  }
  // set up the correct id on our view
  view.id = this.id;
  // link the view to our controller
  view._controller = this;
  // and remember our view
  this._view = view;
  // let our object perform more setup code
  this.viewDidLoad();
  // do post-loading processing
  this.processView();
  //
  this.viewWasProcessed = true;
};

TKController.prototype.loadFragment = function (directory, id) {
  var imported_fragment = null;
  //
  var request = new XMLHttpRequest();
  var failed = false;
  request.open('GET', directory + '/' + id + '.html', false);
  try {
    request.send();
  } catch (err) {
    // iTunes will throw an error if the request doesn't exist
    // when using the booklet:// scheme
    // Mark the error here so we can take the FAIL path below, which
    // is actually what we want.
    failed = true;
  }
  // everything went well
  // XXX: we should do more work to differentitate between http:// and file:// URLs here
  if (!failed && ((request.status <= 0 && request.responseText !== '') || request.status == 200)) {
    // XXX: this is way dirty
    var loaded_fragment = document.implementation.createHTMLDocument();
    loaded_fragment.write(request.responseText);
    imported_fragment = document.importNode(loaded_fragment.getElementById(id), true);
  }
  return imported_fragment;
};

/**
 *  This method is called once the view has been loaded and allows the controller to post-process it.
 */
TKController.prototype.processView = function () {
  var view = this._view;
  // restore properties that have not been set yet since construction
  this.restoreProperty('navigatesTo');
  this.restoreProperty('actions');
  this.restoreProperty('outlets');
  this.restoreProperty('backButton');
  this.restoreProperty('scrollable');
  // process highlightedElement
  if (this.highlightedElement !== null && !(this.highlightedElement instanceof Element)) {
    this.highlightedElement =  this._view.querySelector(this.highlightedElement);
  }
  // process links
  var links = view.querySelectorAll('a');
  for (var i = 0; i < links.length; i++) {
    this.addNavigableElement(links[i]);
  }
  // process assets to pre-load
  for (var i = 0; i < this.preloads.length; i++) {
    new Image().src = this.preloads[i];
  }
};

TKController.prototype.restoreProperty = function (property) {
  var value = this.propertiesToRestoreOnLoad[property];
  if (value !== undefined && this['_' + property] === null) {
    this[property] = value;
  }
};

TKController.prototype.getArchivedProperty = function (property) {
  var archived_value;
  try {
    var archived_value = bookletController.archive.controllers[this.id][property];
  }
  catch (e) {}
  return archived_value;
};

/**
 *  Indicates whether the view the controller manages was loaded yet.
 *
 *  @returns {bool} Whether the view was loaded yet.
 */
TKController.prototype.isViewLoaded = function () {
  return (this._view !== null);
};

/* ==================== Dealing with the various properties ==================== */

/**
 *  @name TKController.prototype
 *  @property {Array} navigatesTo A list of objects defining elements to act as anchors to navigate to other controllers. Each object in the array is an
 *  ad-hoc object with <code>selector</code> and <code>controller</code> properties. The <code>selector</code> is a string describing a CSS selector used
 *  to match the element within the {@link #view} that will act as an anchor to navigate to the controller. The <code>controller</code> is either a string matching
 *  the {@link #id} of an existing controller or an reference to a {@link TKController}.
 */
TKController.prototype.setNavigatesTo = function (navigatesTo) {
  if (navigatesTo === null) {
    return;
  }
  // unregister the previous elements if we have any
  if (this._navigatesTo !== null) {
    for (var i = 0; i < this._navigatesTo.length; i++) {
      var element = this._navigatesTo[i];
      element._navigationData = undefined;
      this.removeNavigableElement(element);
    }
  }
  // register the new elements
  this._navigatesTo = [];
  for (var i = 0; i < navigatesTo.length; i++) {
    var item = navigatesTo[i];
    var element = this._view.querySelector(item.selector);
    if (element) {
      element._navigationData = item;
      this._navigatesTo.push(element);
      this.addNavigableElement(element);
    }
  }
};

/**
 *  @name TKController.prototype
 *  @property {Array} actions A list of objects defining elements to act as anchors to trigger a JavaScript callback. Each object in the array is an
 *  ad-hoc object with <code>selector</code>, <code>action</code> and, optionally, <code>arguments</code> properties. The <code>selector</code> is a
 *  string describing a CSS selector used to match the element within the {@link #view} that will act as a trigger for the action. The <code>action</code>
 *  specifies the function to call when the action is triggered, which is either a string matching the name of a method on this controller instance or
 *  a direct reference to a function. Optionally, the <code>arguments</code> property can be specified in order to provide a list of arguments to be passed
 *  to the callback when the action is triggered.
 */
TKController.prototype.setActions = function (actions) {
  if (actions === null || this._actions === actions) {
    return;
  }
  // unregister the previous elements if we have any
  if (this._actions !== null) {
    for (var i = 0; i < this._actions.length; i++) {
      var element = this._actions[i];
      element._actionData = undefined;
      this.removeNavigableElement(element);
    }
  }
  // register the new elements
  this._actions = [];
  for (var i = 0; i < actions.length; i++) {
    var item = actions[i];
    var element = this._view.querySelector(item.selector);
    if (element) {
      element._actionData = item;
      this._actions.push(element);
      this.addNavigableElement(element);
    }
  }
};

/**
 *  @name TKController.prototype
 *  @property {Array} outlets A list of objects defining elements to which we want to create an automatic reference on the controller instance. Each object in
 *  the array has a <code>selector</code> and a <code>name</code> property. The <code>selector</code> is a string describing a CSS selector used to match the   
 *  element within the {@link #view} to which we want to create a reference. The <code>name</code> specifies the name of the JavaScript property that will be holding 
 *  that reference on the controller instance.
 */
TKController.prototype.setOutlets = function (outlets) {
  if (outlets === null) {
    return;
  }
  // unregister the previous outlets if we have any
  if (this._outlets !== null) {
    for (var i = 0; i < this._outlets.length; i++) {
      this[this._outlets[i]] = undefined;
    }
  }
  // register the new outlets
  for (var i = 0; i < outlets.length; i++) {
    var item = outlets[i];
    this[item.name] = this._view.querySelector(item.selector);
  }
  this._outlets = outlets;
};

/**
 *  @name TKController.prototype
 *  @property {String} backButton A CSS selector that matches an element in the {@link #view} that acts as the back button.
 */
TKController.prototype.setBackButton = function (backButton) {
  if (backButton === null) {
    return;
  }
  // forget the old back button if we have one
  if (this._backButton !== null) {
    this._backButton._backButton = undefined;
    // restore display type on ATV
    if (IS_APPLE_TV) {
      this._backButton.style.display = this._backButton._previousDisplayStyle;
    }
    this.removeNavigableElement(this._backButton);
  }
  // set up the new one
  if (backButton !== null) {
    var element = this._view.querySelector(backButton);
    element._backButton = true;
    // hide it on ATV
    if (IS_APPLE_TV) {
      element._previousDisplayStyle = element.style.display;
      element.style.display = 'none';
    }
    this.addNavigableElement(element);
    this._backButton = element;
  }
};

/* ==================== Notification Methods ==================== */

/**
 *  This method is called when the view has been fully loaded but not yet processed. Override this method in order to customize the content of the view.
 */
TKController.prototype.viewDidLoad = function () {};
TKController.prototype.viewDidUnload = function () {};

TKController.prototype._viewWillAppear = function () {};
/**
 *  This method is called when the view managed by this controller is about to appear on screen, probably after an animated transition.
 */
TKController.prototype.viewWillAppear = function () {};

TKController.prototype._viewDidAppear = function () {};
/**
 *  This method is called when the view managed by this controller appeared on screen, probably after an animated transition.
 */
TKController.prototype.viewDidAppear = function () {};

TKController.prototype._viewWillDisappear = function () {};
/**
 *  This method is called when the view managed by this controller is about to disappear from the screen, probably after an animated transition.
 */
TKController.prototype.viewWillDisappear = function () {};

TKController.prototype._viewDidDisappear = function () {};
/**
 *  This method is called when the view managed by this controller has disappeared from the screen, probably after an animated transition.
 */
TKController.prototype.viewDidDisappear = function () {};

/* ==================== Event Handling ==================== */

/**
 *  Entry point for all event handling, since <code>TKController</code> implements the DOM <code>EventListener</code> protocol. This method may be subclassed
 *  but it is important to call the superclass's implementation of this method as essential event routing happens there.
 *
 *  @param {Event} event The event.
 */
TKController.prototype.handleEvent = function (event) {
  switch (event.type) {
    case 'click' : 
      this.elementWasActivated(event.currentTarget);
      break;
    case 'highlight' : 
      this.elementWasHighlighted(event.currentTarget, event.relatedTarget);
      break;
    case 'unhighlight' : 
      this.elementWasUnhighlighted(event.currentTarget, event.relatedTarget);
      break;
    case 'mouseover' : 
      this.elementWasHovered(event.currentTarget);
      break;
    case 'mouseout' : 
      this.elementWasUnhovered(event.currentTarget);
      break;
    case 'DOMNodeInsertedIntoDocument' : 
      this.viewWasInsertedIntoDocument(event);
      break;
  }
};

/**
 *  Triggered when an element is activated by the user, no matter what the host's input methods are as TuneKit abstracts the interaction that yields
 *  an element's activation. This method may be subclassed but it is important to call the superclass's implementation of this method as navigation anchors,
 *  actions, etc. are handled in that method directly.
 *
 *  @param {Element} element The element that was just activated.
 */
TKController.prototype.elementWasActivated = function (element) {
  if (element._navigationData !== undefined) {
    // pointer to the controller
    var controller = TKController.resolveController(element._navigationData.controller);
    // error if we have an undefined object
    if (controller === undefined) {
      console.error('TKController.elementWasActivated: trying to push an undefined controller');
      return;
    }
    // otherwise, navigate to it
    TKSpatialNavigationManager.sharedManager.highlightElement(element);
    TKNavigationController.sharedNavigation.pushController(controller);
  }
  else if (element._actionData !== undefined) {
    TKSpatialNavigationManager.sharedManager.highlightElement(element);
    // get the callback for this action
    var callback = element._actionData.action;
    // see if it's a string in which case we need to get the function dynamically
    if (TKUtils.objectIsString(callback) && TKUtils.objectHasMethod(this, callback)) {
      callback = this[element._actionData.action];
    }
    // see if we have custom arguments
    if (TKUtils.objectIsArray(element._actionData.arguments)) {
      callback.apply(this, element._actionData.arguments);
    }
    // otherwise just call the callback
    else {
      callback.apply(this);
    }
  }
  else if (element._backButton !== undefined) {
    TKSpatialNavigationManager.soundToPlay = SOUND_EXIT;
    TKSpatialNavigationManager.sharedManager.highlightElement(element);
    TKNavigationController.sharedNavigation.popController();
  }
  else if (element.localName == 'a' && IS_APPLE_TV) {
    element.dispatchEvent(TKUtils.createEvent('click', null));
  }
  else if (element._scrollableData !== undefined) {
    this.scrollWithData(element._scrollableData);
  }
};

/**
 *  Triggered when an element receives highlight.
 *
 *  @param {Element} element The element that is newly being highlighted.
 *  @param {Element} previouslyHighlightedElement The element that previously was highlighted, or <code>null</code> if there was none.
 */
TKController.prototype.elementWasHighlighted = function (element, previouslyHighlightedElement) {
};

/**
 *  Triggered when an element loses highlight.
 *
 *  @param {Element} element The element that is newly being highlighted.
 *  @param {Element} nextHighlightedElement The element that is going to be highlighted next, or <code>null</code> if there is none.
 */
TKController.prototype.elementWasUnhighlighted = function (element, nextHighlightedElement) {
};

/**
 *  Triggered when an element is hovered, which only happens when a mouse is present.
 *
 *  @param {Element} element The element that is being hovered.
 */
TKController.prototype.elementWasHovered = function (element) {
};

/**
 *  Triggered when an element is not hovered any longer, which only happens when a mouse is present.
 *
 *  @param {Element} element The element that is not hovered any longer.
 */
TKController.prototype.elementWasUnhovered = function (element) {
};

/**
 *  Triggered when the view is first inserted into the document.
 */
TKController.prototype.viewWasInsertedIntoDocument = function () {
  this.viewNeverAppeared = false;
};

/**
 *  Indicates whether the receiver is a descendent of the controller passed as an argument.
 *
 *  @param {TKController} purportedParentController The controller that we assume is a parent controller to the receiver.
 *  @returns {bool} Whether the controller is a descendent of the other controller passed as a parameter.
 */
TKController.prototype.isDescendentOfController = function (purportedParentController) {
  var is_descendent = false;
  var parent = this.parentController;
  while (parent !== null) {
    if (parent === purportedParentController) {
      is_descendent = true;
      break;
    }
    parent = parent.parentController;
  }
  return is_descendent;
};

/* ==================== Keyboard Navigation ==================== */

/**
 *  Adds an element within the controller's view to the list of navigable elements. Any element that is interactive should be registered as navigable, even
 *  when a mouse is available.
 *
 *  @param {Element} element The element we wish to make navigable.
 */
TKController.prototype.addNavigableElement = function (element) {
  // nothing to do if we already know about this element
  if (this._navigableElements.indexOf(element) > -1) {
    return;
  }
  //
  if (!IS_APPLE_TV) {
    element.addEventListener('click', this, false);
  }
  element.addEventListener('highlight', this, false);
  element.addEventListener('unhighlight', this, false);
  element._controller = this;
  //
  this._navigableElements.push(element);
  //
  TKSpatialNavigationManager.sharedManager.addNavigableElement(element);
};

/**
 *  Removes an element within the controller's view from the list of navigable elements.
 *
 *  @param {Element} element The element we wish to remove from the navigable elements list.
 */
TKController.prototype.removeNavigableElement = function (element) {
  // find the index for this element
  var index = this._navigableElements.indexOf(element);
  if (index < 0) {
    return;
  }
  //
  element.removeEventListener('click', this, false);
  element.removeEventListener('highlight', this, false);
  element.removeEventListener('unhighlight', this, false);
  element._controller = undefined;
  // remove elements from the tracking arrays
  this._navigableElements.splice(index, 1);
  //
  TKSpatialNavigationManager.sharedManager.removeNavigableElement(element);
};

/**
 *  Allows to specify custom metrics for an element displayed on screen. This method is called by the spatial navigation manager when determining what the
 *  element to highlight is after the uses presses a directional key on the Apple remote. By default, the CSS metrics for the elements are used, but in
 *  certain cases the author may wish to use different metrics that are more logical for the navigation. Return <code>null</code> in order to specify that
 *  the element has no custom metrics.
 *
 *  @param {Element} element The element which the spatial navigation manager is inspecting.
 *  @returns {TKRect} The custom metrics for the given element.
 */
TKController.prototype.customMetricsForElement = function (element) {
  return null;
};

/**
 *  Allows the controller to provide the spatial navigation manager with a prefered element to highlight, overriding the default behavior of using CSS metrics.
 *  The default implementation returns <code>undefined</code>, which indicates that the automatic behavior should be used, while returning <code>null</code> 
 *  means that there should be no element highlighted in the provided direction.
 *
 *  @param {Element} currentElement The element that is currently highlighted.
 *  @param {int} direction The direction the user is navigation towards.
 *  @returns {Element} The preferred element to highlight in the provided direction.
 */
TKController.prototype.preferredElementToHighlightInDirection = function (currentElement, direction) {
  return undefined;
};

// private method meant to be over-ridden by a controller sub-classes to provide a custom element
// to highlight, returning null means there's nothing custom to report
// XXX: we really need a better mechanism to do this stuff, having a private method for subclasses and one for instances is way dirty
TKController.prototype._preferredElementToHighlightInDirection = function (currentElement, direction) {
  return undefined;
};

/* ==================== Scrolling ==================== */

TKController.prototype.setScrollable = function (scrollable) {
  // remove all scrollable regions if we already had some set up
  if (this._scrollable !== null) {
    for (var i = 0; i < this._scrollable.length; i++) {
      var element = this._scrollable[i];
      element._scrollableData = undefined;
      this.removeNavigableElement(element);
    }
  }
  // process scrollable regions
  this._scrollable = [];
  for (var i = 0; i < scrollable.length; i++) {
    var scrollable_data = scrollable[i];
    // create an animator for this scrollable element
    scrollable_data.animator = new TKAnimator(TKControllerScrollDuration, null, TKControllerScrollSpline);
    // check if we have an up element
    if (scrollable_data.up !== undefined) {
      var up_button = this._view.querySelector(scrollable_data.up);
      up_button._scrollableData = {
        direction: TKControllerScrollDirectionUp,
        target: scrollable_data.target,
        animator: scrollable_data.animator
      };
      this._scrollable.push(up_button);
      this.addNavigableElement(up_button);
    }
    // check if we have a down element
    if (scrollable_data.down !== undefined) {
      var down_button = this._view.querySelector(scrollable_data.down);
      down_button._scrollableData = {
        direction: TKControllerScrollDirectionDown,
        target: scrollable_data.target,
        animator: scrollable_data.animator
      };
      this._scrollable.push(down_button);
      this.addNavigableElement(down_button);
    }
    // check if we have a left element
    if (scrollable_data.left !== undefined) {
      var left_button = this._view.querySelector(scrollable_data.left);
      left_button._scrollableData = {
        direction: TKControllerScrollDirectionLeft,
        target: scrollable_data.target,
        animator: scrollable_data.animator
      };
      this._scrollable.push(left_button);
      this.addNavigableElement(left_button);
    }
    // check if we have a right element
    if (scrollable_data.right !== undefined) {
      var right_button = this._view.querySelector(scrollable_data.right);
      right_button._scrollableData = {
        direction: TKControllerScrollDirectionRight,
        target: scrollable_data.target,
        animator: scrollable_data.animator
      };
      this._scrollable.push(right_button);
      this.addNavigableElement(right_button);
    }
  }
};

TKController.prototype.scrollWithData = function (scrollData) {
  // stop any running animation for this scrollable region
  scrollData.animator.stop();
  // get a pointer to the target element
  var element = this._view.querySelector(scrollData.target);
  // stop right there if there's no such element
  if (!(element instanceof Element)) {
    TKSpatialNavigationManager.soundToPlay = SOUND_LIMIT;
    return;
  }
  // figure out which direction we're scrolling
  var vertical_scrolling = (scrollData.direction == TKControllerScrollDirectionUp || scrollData.direction == TKControllerScrollDirectionDown);
  // get the increment for this scroll
  var increment = element[vertical_scrolling ? 'offsetHeight' : 'offsetWidth'] * TKControllerScrollIncrementFraction;
  // get the start value
  var start_value = element[vertical_scrolling ? 'scrollTop' : 'scrollLeft'];
  // get the target value
  var target_value;
  if (scrollData.direction == TKControllerScrollDirectionUp) {
    target_value = Math.max(element.scrollTop - increment, 0);
  }
  else if (scrollData.direction == TKControllerScrollDirectionDown) {
    target_value = Math.min(element.scrollTop + increment, element.scrollHeight - element.offsetHeight);
  }
  else if (scrollData.direction == TKControllerScrollDirectionLeft) {
    target_value = Math.max(element.scrollLeft - increment, 0);
  }
  else if (scrollData.direction == TKControllerScrollDirectionRight) {
    target_value = Math.min(element.scrollLeft + increment, element.scrollWidth - element.offsetWidth);
  }
  // only run if we have different values
  if (start_value == target_value) {
    TKSpatialNavigationManager.soundToPlay = SOUND_LIMIT;
    return;
  }
  // set the delegate
  scrollData.animator.delegate = {
    animationDidIterate : function (fraction) {
      element[vertical_scrolling ? 'scrollTop' : 'scrollLeft'] = start_value + fraction * (target_value - start_value);
    }
  }
  // start the animation
  scrollData.animator.start();
  // play the move sound since we're scrolling
  TKSpatialNavigationManager.soundToPlay = SOUND_MOVED;
};

TKController.prototype.scrollUp = function () {
  this.upScrollData.target = this.scrollableElement;
  this.scrollWithData(this.upScrollData);
};

TKController.prototype.scrollDown = function () {
  this.downScrollData.target = this.scrollableElement;
  this.scrollWithData(this.downScrollData);
};

/* ==================== Keyboard Navigation ==================== */

/**
 *  Indicates whether the controller is interested in providing event handling for the key with the given identifier. By default, this method returns
 *  <code>false</code>, letting the spatial navigation manager take care of the event in order to perform navigation. In case the method returns 
 *  <code>true</code>, the {@link #keyWasPressed} method is called to let the controller provide its own custom key event handling.
 *
 *  @param {int} key The identifier for the key that was pressed.
 *  @returns {bool} Whether the controller wants to provide its own custom key event handling.
 */
TKController.prototype.wantsToHandleKey = function (key) {
  return (this.scrollableElement !== null && (key == KEYBOARD_UP || key == KEYBOARD_DOWN));
};

/**
 *  Triggered when a key was pressed and the receiver has expressed explicit interest in providing custom key event handling by returning <code>true</code> in
 *  the {@link #wantsToHandleKey} method.
 *
 *  @param {int} key The identifier for the key that was pressed.
 */
TKController.prototype.keyWasPressed = function (key) {
  // up should scroll
  if (key == KEYBOARD_UP) {
    this.scrollUp();
  }
  // down should scroll
  else if (key == KEYBOARD_DOWN) {
    this.scrollDown();
  }
  // done, play the sound
  TKUtils.playSound(TKSpatialNavigationManager.soundToPlay);
};

/* ==================== Archival ==================== */

/**
 *  Called when the booklet's state is being archived. This method needs to return a list of properties reflecting the current state for the receiver.
 *
 *  @returns {Object} The list of properties to archive as a hash-like object.
 *  @private
 */
TKController.prototype.archive = function () {
  var archive = {
    id: this.id
  };
  // see if we can add a highlighted element index
  if (this.highlightedElement !== null) {
    archive.highlightedElementIndex = this.navigableElements.indexOf(this.highlightedElement);
  }
  //
  return archive;
};

TKClass(TKController);
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

/* ==================== TKSpatialNavigationManager ==================== */

/**
 *  Indicates whether the spatial navigation manager is enabled, which currently is only the case on Apple TV, or within Safari for development purposes.
 *  @constant
 *  @type bool
 */
const TKSpatialNavigationManagerEnabled = (window.iTunes === undefined || window.iTunes.platform == 'AppleTV') ? true : (parseInt(window.iTunes.version, 0) < 9);

/**
 *  The CSS class name applied to an element when it is highlighted by the spatial navigation manager.
 *  @constant
 *  @type String
 */
const TKSpatialNavigationManagerHighlightCSSClass = 'tk-highlighted';
/**
 *  The CSS class name an element should have in order to be ignored by the spatial navigation manager.
 *  @constant
 *  @type String
 */
const TKSpatialNavigationManagerInactiveCSSClass = 'tk-inactive';

/**
 *  The up direction.
 *  @constant
 *  @type int
 */
const TKSpatialNavigationManagerDirectionUp = KEYBOARD_UP;
/**
 *  The right direction.
 *  @constant
 *  @type int
 */
const TKSpatialNavigationManagerDirectionRight = KEYBOARD_RIGHT;
/**
 *  The down direction.
 *  @constant
 *  @type int
 */
const TKSpatialNavigationManagerDirectionDown = KEYBOARD_DOWN;
/**
 *  The left direction.
 *  @constant
 *  @type int
 */
const TKSpatialNavigationManagerDirectionLeft = KEYBOARD_LEFT;
/**
 *  The list of keys the spatial navigation manager knows how to handle.
 *  @constant
 *  @type int
 *  @private
 */
const TKSpatialNavigationManagerKnownKeys = [KEYBOARD_UP, KEYBOARD_RIGHT, KEYBOARD_DOWN, KEYBOARD_LEFT, KEYBOARD_BACKSPACE, KEYBOARD_RETURN];

/**
 *  The number of controllers that are currently busy, when for instance performing a transition that should not be interrupted. When this variable is more than
 *  <code>0</code>, key handling by the spatial navigation manager is suspended.
 *  @type int
 */
TKSpatialNavigationManager.busyControllers = 0;
/**
 *  The identifier for the sound to play for the current event loop.
 *  @type int
 */
TKSpatialNavigationManager.soundToPlay = null;

/* ==================== Creating the shared instance lazily ==================== */

/**
 *  @name TKSpatialNavigationManager
 *  @property {TKSpatialNavigationManager} sharedManager The shared instance of the spatial navigation manager. TuneKit automatically creates a single instance
 *  of the {@link TKSpatialNavigationManager} class as needed, and developers should never have to create an instance themselves, instead using this property
 *  to retrieve the shared instance.
 */
TKSpatialNavigationManager._sharedManager = null;
TKSpatialNavigationManager.__defineGetter__('sharedManager', function () {
  if (this._sharedManager === null) {
    this._sharedManager = new TKSpatialNavigationManager();
  }
  return this._sharedManager;
});

/* ==================== Constructor ==================== */

TKSpatialNavigationManager.inherits = TKObject;
TKSpatialNavigationManager.includes = [TKEventTriage];
TKSpatialNavigationManager.synthetizes = ['managedController'];

/**
 *  @class
 *
 *  <p>The spatial navigation manager is a special controller type that sits behind the scenes and handles much of the keyboard interaction in order
 *  to provide navigation between navigable elements of the {@link #managedController}. By default, navigation between navigable elements is automatic and
 *  performed based on the location and metrics of each elements. The elements' metrics are those set by CSS and a controller is free to provide custom
 *  metrics for elements as it sees fit by implementing the {@link TKController#customMetricsForElement} method. Additionally, the automatic navigation
 *  can be completely bypassed should the managed controller provide a custom element to navigate to with the
 *  {@link TKController#preferredElementToHighlightInDirection} method.</p>
 *
 *  @extends TKObject
 *  @since TuneKit 1.0
 */
function TKSpatialNavigationManager () {
  this.callSuper();
  //
  this._managedController = null;
  /**
   *  The complete list of all elements that can be navigated to within this controller and all of its sub-controllers.
   *  @type Array
   */
  this.navigableElements = [];
  this.highlightedElement = null;
  this.previousNavigation = null;
  // register for keyboard events if we're running outside of the iTunes app
  if (TKSpatialNavigationManagerEnabled) {
    window.addEventListener('keydown', this, true);
  }
};

/**
 *  @name TKSpatialNavigationManager.prototype
 *  @property managedController The managed controller is the controller that the spatial navigation manager queries for navigable elements
 *  and any customization of the otherwise automated navigation. Developers should not assign this property directly as the navigation controller takes care of
 *  that as the user navigates through controllers.
 *  @type TKController
 */
TKSpatialNavigationManager.prototype.setManagedController = function (controller) {
  this._managedController = controller;
  this.navigableElements = controller.navigableElements;
  this.previousNavigation = null;
  // is this the first time we're managing this controller?
  if (controller._wasAlreadyManagedBySpatialNavigationManager === undefined) {
    // see if it had an archived highlighted element
    var archived_index = controller.getArchivedProperty('highlightedElementIndex');
    if (archived_index !== undefined) {
      var archived_element = controller.navigableElements[archived_index];
      if (archived_element instanceof Element) {
        controller.highlightedElement = archived_element;
      }
    }
    // track that we've managed it before
    controller._wasAlreadyManagedBySpatialNavigationManager = true;
  }
  // reset the highlighted element to be nothing
  this.highlightedElement = null;
  // if we have a preferred or recorded highlighted element, highlight that
  if (controller.highlightedElement !== null) {
    this.highlightElement(controller.highlightedElement);
  }
  // otherwise default to the top-most element
  else {
    this.highlightTopElement();
  }
};

TKSpatialNavigationManager.prototype.registerController = function (controller) {
  var elements = controller.navigableElements;
  for (var i = 0; i < elements.length; i++) {
    this.addNavigableElement(elements[i]);
  }
};

TKSpatialNavigationManager.prototype.unregisterController = function (controller) {
  var elements = controller.navigableElements;
  for (var i = 0; i < elements.length; i++) {
    this.removeNavigableElement(elements[i]);
  }
};

TKSpatialNavigationManager.prototype.addNavigableElement = function (element) {
  // nothing to do if the new element is not rooted in the managed hierarchy or we already know it
  if (!element._controller.isDescendentOfController(this._managedController) ||
      this.navigableElements.indexOf(element) > -1) {
    return;
  }
  // and keep track of it
  this.navigableElements.push(element);
};

TKSpatialNavigationManager.prototype.removeNavigableElement = function (element) {
  // find the index for this element
  var index = this.navigableElements.indexOf(element);
  if (index < 0) {
    return;
  }
  // remove elements from the tracking arrays
  this.navigableElements.splice(index, 1);
};

/* ==================== Keyboard Navigation ==================== */

TKSpatialNavigationManager.prototype.handleKeydown = function (event) {

  var key = event.keyCode;

  // check if our controller knows what it's doing and let it take over in case it does
  if (this._managedController.wantsToHandleKey(key)) {
    // prevent default actions
    event.stopPropagation();
    event.preventDefault();
    // have the controller do what it think is best in this case
    this._managedController.keyWasPressed(key);
    return;
  }

  // reset the sound
  TKSpatialNavigationManager.soundToPlay = null;

  // check we know about this key, otherwise, do nothing
  if (TKSpatialNavigationManagerKnownKeys.indexOf(key) == -1) {
    return;
  }

  var navigation = TKNavigationController.sharedNavigation;
  // first, check if we're hitting the back button on the home screen, in which case
  // we don't want to do anything and let the User Agent do what's right to exit
  if (event.keyCode == KEYBOARD_BACKSPACE && navigation.topController === homeController) {
    return;
  }
  
  // before we go any further, prevent the default action from happening
  event.stopPropagation();
  event.preventDefault();
  
  // check if we're busy doing other things
  if (TKSpatialNavigationManager.busyControllers > 0) {
    return;
  }
  // see if we pressed esc. so we can pop to previous controller
  if (event.keyCode == KEYBOARD_BACKSPACE) {
    var top_controller = navigation.topController;
    if (top_controller !== homeController) {
      // at any rate, play the exit sound
      TKUtils.playSound(SOUND_EXIT);
      // see if the top controller has a custom place to navigate to with the back button
      if (top_controller.backButton instanceof Element && top_controller.backButton._navigationData !== undefined) {
        navigation.pushController(TKController.resolveController(top_controller.backButton._navigationData.controller));
      }
      // otherwise, just pop the controller
      else {
        navigation.popController();
      }
    }
  }
  // check if we want to activate an element
  else if (key == KEYBOARD_RETURN) {
    if (this.highlightedElement !== null) {
      var success = this.highlightedElement._controller.elementWasActivated(this.highlightedElement);
      TKUtils.playSound(TKSpatialNavigationManager.soundToPlay === null ? SOUND_ACTIVATED : TKSpatialNavigationManager.soundToPlay);
    }
    else {
      TKUtils.playSound(SOUND_LIMIT);
    }
  }
  // keyboard nav
  else {
    var key_index = TKSpatialNavigationManagerKnownKeys.indexOf(key);
    // do nothing if we don't have any highlightable elements or don't know about this navigation direction
    if (this.navigableElements.length == 0 || key_index == -1) {
      TKUtils.playSound(SOUND_LIMIT);
      return;
    }
    // figure the index of the element to highlight
    var index = this.nearestElementIndexInDirection(key);

    // get a pointer to the controller of the previous item if we have one
    if (this.highlightedElement !== null) {
      var previous_controller = this.highlightedElement._controller;

      // see if we're being provided custom navigation by the controller instance
      var provided_preferred_element = false;
      var preferred_highlighted_element = previous_controller.preferredElementToHighlightInDirection(this.highlightedElement, key);
      // try again with the private method meant to be implemented by the sub-class
      if (preferred_highlighted_element === undefined) {
        preferred_highlighted_element = previous_controller._preferredElementToHighlightInDirection(this.highlightedElement, key);
      }
      // we explicitly do not want to highlight anything
      if (preferred_highlighted_element === null) {
        index = -1;
      }
      else if (preferred_highlighted_element !== undefined) {
        var preferred_highlight_index = this.navigableElements.indexOf(preferred_highlighted_element);
        // if this element is in our navigation list and is ready to be navigated to
        if (preferred_highlight_index >= 0 && this.isElementAtIndexNavigable(preferred_highlight_index)) {
          index = preferred_highlight_index;
          provided_preferred_element = true;
        }
      }

      // stop right there if we have no useful index
      if (index == -1) {
        TKUtils.playSound(SOUND_LIMIT);
        return;
      }
    }

    // get a pointer to the controller of the item we consider highlighting now
    var next_controller = this.navigableElements[index]._controller;

    // we're moving out of a tab controller into one controller managed by that tab controller
    // in which case we want to highlight the first item in that controller based on its orientation
    if (previous_controller instanceof TKTabController &&
        this.highlightedElement._tabIndex !== undefined &&
        next_controller.parentController === previous_controller) {
      index = this.navigableElements.indexOf(next_controller.highlightedElement || next_controller.navigableElements[0]);
    }
    // we're moving back to a tab element from an element managed by a controller
    // that is itself managed by the very tab controller we're focusing, so let's highlight
    // the element that is selected in that tab controller
    else if (next_controller instanceof TKTabController &&
             this.navigableElements[index]._tabIndex !== undefined &&
             previous_controller.parentController === next_controller) {
      index = this.navigableElements.indexOf(next_controller.tabs[next_controller.selectedIndex]);
    }
    // check if we were doing the reverse operation to the last one
    else if (!provided_preferred_element && this.previousNavigation !== null && key_index == (this.previousNavigation.keyIndex + 2) % 4) {
      var previous_element_index = this.navigableElements.indexOf(this.previousNavigation.element);
      if (previous_element_index > -1 && this.isElementAtIndexNavigable(previous_element_index)) {
        index = previous_element_index;
      }
    }
    
    // get a pointer to the next element to highlight
    var next_highlighted_element = (index >= 0 && index < this.navigableElements.length) ? this.navigableElements[index] : null;
    
    // only highlight if we know what element to highlight
    if (next_highlighted_element !== null && next_highlighted_element.isNavigable()) {
      // track the interaction so we can go back to it
      if (this.highlightedElement !== null) {
        this.previousNavigation = {
          element: this.highlightedElement,
          keyIndex : key_index
        };
      }
      this.highlightElement(next_highlighted_element);
      TKUtils.playSound(SOUND_MOVED);
    }
    else {
      TKUtils.playSound(SOUND_LIMIT);
    }
  }
};

TKSpatialNavigationManager.prototype.nearestElementIndexInDirection = function (direction) {
  // nothing to do if we don't have a next element
  if (this.highlightedElement === null) {
    if (direction == TKSpatialNavigationManagerDirectionUp) {
      return this.bottomMostIndex();
    }
    else if (direction == TKSpatialNavigationManagerDirectionRight) {
      return this.leftMostIndex();
    }
    else if (direction == TKSpatialNavigationManagerDirectionDown) {
      return this.topMostIndex();
    }
    else if (direction == TKSpatialNavigationManagerDirectionLeft) {
      return this.rightMostIndex();
    }    
  }
  // figure out parameters
  var ref_position, target_edge;
  if (direction == TKSpatialNavigationManagerDirectionUp) {
    ref_position = TKRectMiddleOfTopEdge;
    target_edge = TKRectBottomEdge;
  }
  else if (direction == TKSpatialNavigationManagerDirectionRight) {
    ref_position = TKRectMiddleOfRightEdge;
    target_edge = TKRectLeftEdge;
  }
  else if (direction == TKSpatialNavigationManagerDirectionDown) {
    ref_position = TKRectMiddleOfBottomEdge;
    target_edge = TKRectTopEdge;
  }
  else if (direction == TKSpatialNavigationManagerDirectionLeft) {
    ref_position = TKRectMiddleOfLeftEdge;
    target_edge = TKRectRightEdge;
  }
  // look for the closest element now
  var index = -1;
  var min_d = 10000000;
  var highlight_index = this.navigableElements.indexOf(this.highlightedElement);
  var ref_metrics = this.metricsForElement(this.highlightedElement);
  var ref_point = ref_metrics.pointAtPosition(ref_position);
  var ref_center = ref_metrics.pointAtPosition(TKRectCenter);
  for (var i = 0; i < this.navigableElements.length; i++) {
    // see if we should skip this element
    if (!this.isElementAtIndexNavigable(i)) {
      continue;
    }
    var metrics = this.metricsForElement(this.navigableElements[i]);
    // go to next item if it's not in the right direction or already has highlight
    if ((direction == TKSpatialNavigationManagerDirectionUp && metrics.pointAtPosition(TKRectBottomLeftCorner).y > ref_center.y) ||
        (direction == TKSpatialNavigationManagerDirectionRight && metrics.pointAtPosition(TKRectTopLeftCorner).x < ref_center.x) ||
        (direction == TKSpatialNavigationManagerDirectionDown && metrics.pointAtPosition(TKRectTopLeftCorner).y < ref_center.y) ||
        (direction == TKSpatialNavigationManagerDirectionLeft && metrics.pointAtPosition(TKRectTopRightCorner).x > ref_center.x) ||
        i == highlight_index) {
      continue;
    }
    var d = metrics.edge(target_edge).distanceToPoint(ref_point);
    if (d < min_d) {
      min_d = d;
      index = i;
    }
  }
  // return the index, if any
  return index;
};

TKSpatialNavigationManager.prototype.topMostIndex = function () {
  var index = 0;
  var min_y = 10000;
  for (var i = 0; i < this.navigableElements.length; i++) {
    if (!this.isElementAtIndexNavigable(i)) {
      continue;
    }
    var y = this.metricsForElementAtIndex(i).y;
    if (y < min_y) {
      min_y = y;
      index = i;
    }
  }
  return index;
};

TKSpatialNavigationManager.prototype.rightMostIndex = function () {
  var index = 0;
  var max_x = 0;
  for (var i = 0; i < this.navigableElements.length; i++) {
    if (!this.isElementAtIndexNavigable(i)) {
      continue;
    }
    var x = this.metricsForElementAtIndex(i).pointAtPosition(TKRectTopRightCorner).x;
    if (x > max_x) {
      max_x = x;
      index = i;
    }
  }
  return index;
};

TKSpatialNavigationManager.prototype.bottomMostIndex = function () {
  var index = 0;
  var max_y = 0;
  for (var i = 0; i < this.navigableElements.length; i++) {
    if (!this.isElementAtIndexNavigable(i)) {
      continue;
    }
    var y = this.metricsForElementAtIndex(i).pointAtPosition(TKRectBottomRightCorner).y;
    if (y > max_y) {
      max_y = y;
      index = i;
    }
  }
  return index;
};

TKSpatialNavigationManager.prototype.leftMostIndex = function () {
  var index = 0;
  var min_x = 10000;
  for (var i = 0; i < this.navigableElements.length; i++) {
    if (!this.isElementAtIndexNavigable(i)) {
      continue;
    }
    var y = this.metricsForElementAtIndex(i).x;
    if (y < min_x) {
      min_x = y;
      index = i;
    }
  }
  return index;
};

TKSpatialNavigationManager.prototype.metricsForElement = function (element) {
  return element._controller.customMetricsForElement(element) || element.getBounds();
};

TKSpatialNavigationManager.prototype.metricsForElementAtIndex = function (index) {
  return this.metricsForElement(this.navigableElements[index]);
};

/**
 *  Highlight the top-most element in the list of navigable elements.
 */
TKSpatialNavigationManager.prototype.highlightTopElement = function () {
  // now see if we need to enforce some default element
  if (this.navigableElements.length > 0) {
    this.highlightElement(this.navigableElements[this.topMostIndex()]);
  }
};

/**
 *  Indicates whether a given element is navigable at the provided index in the {@link #navigableElements} array.
 *
 *  @param {Element} element The index for the element in the {@link #navigableElements} array.
 *  @returns {bool} Whether the element can be navigated to.
 */
TKSpatialNavigationManager.prototype.isElementAtIndexNavigable = function (index) {
  return this.navigableElements[index].isNavigable();
};

/* ==================== Highlight Management ==================== */

/**
 *  Highlights a given element if it's part of the {@link #navigableElements} array. When an element receives highlight, a <code>highlight</code> event is 
 *  dispatched to that element, while an <code>unhighlight</code> event is dispatched to the element that previously had highlight.
 *
 *  @param {Element} element The element to highlight.
 */
TKSpatialNavigationManager.prototype.highlightElement = function (element) {
  // nothing to do if we don't really have an element to highlight
  if (!(element instanceof Element)) {
    return;
  }
  // check that this element is navigable, and do nothing if it's not
  var navigation_index = this.navigableElements.indexOf(element);
  if (navigation_index == -1 || !this.isElementAtIndexNavigable(navigation_index)) {
    return;
  }
  //
  if (this.highlightedElement !== null) {
    this.highlightedElement.dispatchEvent(TKUtils.createEvent('unhighlight', element));
    if (TKSpatialNavigationManagerEnabled) {
      this.highlightedElement.removeClassName(TKSpatialNavigationManagerHighlightCSSClass);
    }
  }
  //
  element.dispatchEvent(TKUtils.createEvent('highlight', this.highlightedElement));
  if (TKSpatialNavigationManagerEnabled) {
    element.addClassName(TKSpatialNavigationManagerHighlightCSSClass);
  }
  this.highlightedElement = element;
  // track on its controller that it was the last with highlight
  element._controller.highlightedElement = element;
};

TKClass(TKSpatialNavigationManager);
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

/**
 *  @class
 *  @name TKNavigationControllerDelegate
 *  @since TuneKit 1.0
 */

/**
 *  Indicates that a new controller is becoming the top controller and is about to become visible on screen.
 *
 *  @name navigationControllerWillShowController
 *  @function
 *
 *  @param {TKNavigationController} navigationController The navigation controller.
 *  @param {TKController} controller The controller that is about to be shown by the navigation controller.
 *  @memberOf TKNavigationControllerDelegate.prototype
 */
const TKNavigationControllerWillShowController = 'navigationControllerWillShowController';  
/**
 *  Indicates that a new controller has become the top controller and is fully visible on screen.
 *
 *  @name navigationControllerDidShowController
 *  @function
 *
 *  @param {TKNavigationController} navigationController The navigation controller.
 *  @param {TKController} controller The controller that is has been shown by the navigation controller.
 *  @memberOf TKNavigationControllerDelegate.prototype
 */
const TKNavigationControllerDidShowController = 'navigationControllerDidShowController';  

TKNavigationController.inherits = TKController;
TKNavigationController.synthetizes = ['topController'];

/**
 *  @property {TKNavigationController} sharedNavigation The shared instance of the navigation controller. TuneKit automatically creates a single instance
 *  of the {@link TKNavigationController} class as needed, and developers should never have to create an instance themselves, instead using this property
 *  to retrieve the shared instance.
 */
TKNavigationController.sharedNavigation = null;

/**
 *  @class
 *
 *  <p>The spatial navigation manager is a pre-insantiated singleton controller that handles the logic for all navigation between controllers. The currently
 *  showing controller is the {@link #topController}, and is the last item of the {@link #controllers} array, which traces the complete navigation history
 *  from the home controller onwards. By implementing the {@link TKNavigationControllerDelegate} protocol, the navigation controller's {@link #delegate} can
 *  track as the user navigates between controllers. While the {@link TKController#navigatesTo} property should be sufficient to alloe developers to specify
 *  what action triggers a navigation to a given controller, the {@link #pushController} and {@link #popController} methods also allow a programmatic
 *  interaction with the navigation controller.</p>
 *
 *  @extends TKController
 *  @since TuneKit 1.0
 *
 *  @param {Object} data A hash of properties to use as this object is initialized.
 */
function TKNavigationController (data) {
  /**
   *  The list of controllers in the navigation stack. The controller at the first index is the root-most controller, while the controller at the last index is
   *  the top controller.
   *  @type Array
   */
  this.controllers = [];
  /**
   *  The delegate for this navigation controller, an object implementing the {@link TKNavigationControllerDelegate} protocol.
   *  @type Object
   */
  this.delegate = data.delegate || null;
  this.rootController = data.rootController || null;
  this.previousController = null;
  //
  this.busy = false;
  //
  this.callSuper(data);
  // see if we have a stack to restore
  if (bookletController.archive !== undefined) {
    var stack = bookletController.archive.navigationStack;
    var restored_controllers = [];
    for (var i = 0; i < stack.length; i++) {
      var controller = TKController.controllers[stack[i]];
      restored_controllers.push(controller);
      controller.loadView();
    }
    // push the last controller
    this.pushController(restored_controllers[restored_controllers.length - 1]);
    // and fake the controllers stack
    this.controllers = restored_controllers;
  }
  // see if we have a root set up
  else if (this.rootController !== null) {
    this.pushController(this.rootController);
  }
  //
  TKNavigationController.sharedNavigation = this;
};

/* ==================== Controllers ==================== */

/**
 *  @name TKNavigationController.prototype
 *  @property {TKController} topController The controller at the top of the navigation stack of {@link #controllers}.
 */
TKNavigationController.prototype.getTopController = function () {
  return (this.controllers.length > 0) ? this.controllers[this.controllers.length - 1] : null;
};

/**
 *  Pushes a new controller to the top of the navigation stack, triggering an animated transition of the new top controller using its
 *  {@link TKController.becomesActiveTransition} property and the {@link TKController.becomesInactiveTransition} property of the previous {@link #topController}
 *  @param {TKController} controller The controller to push onto the navigation stack.
 */
TKNavigationController.prototype.pushController = function (controller) {
  // do nothing if we're busy
  if (this.busy) {
    return;
  }
  //
  TKTransaction.begin();
  // get pointers to object we'll manipulate
  var previous_controller = this.topController;
  var next_view = controller.view;
  // fire delegate saying we're moving to a new controller
  if (TKUtils.objectHasMethod(this.delegate, TKNavigationControllerWillShowController)) {
    this.delegate[TKNavigationControllerWillShowController](this, controller);
  }
  // put the controller in our array
  this.controllers.push(controller);
  // notify of upcoming change
  if (previous_controller !== null) {
    previous_controller._viewWillDisappear();
    previous_controller.viewWillDisappear();
  }
  controller._viewWillAppear();
  controller.viewWillAppear();
  // add it to the tree
  this.view.appendChild(controller.view);
  //
  if (previous_controller !== null) {
    this.transitionToController(previous_controller, controller);
  }
  else {
    this.busy = true;
    this.transitionDidComplete();
    TKSpatialNavigationManager.sharedManager.managedController = controller;
  }
  //
  TKTransaction.commit();
};

/**
 *  Pops the top {@link #topController} off the navigation stack, triggering an animated transition of the new top controller using its
 *  {@link TKController.becomesActiveTransition} property and the {@link TKController.becomesInactiveTransition} property of the previous {@link #topController}
 */
TKNavigationController.prototype.popController = function () {
  // do nothing if we're busy or if there's nothing to pop
  if (this.busy || this.controllers.length < 2) {
    return;
  }
  TKTransaction.begin();
  // fire delegate saying we're moving to a new controller
  if (TKUtils.objectHasMethod(this.delegate, TKNavigationControllerWillShowController)) {
    this.delegate[TKNavigationControllerWillShowController](this, this.controllers[this.controllers.length - 2]);
  }
  // update stack
  var previous_controller = this.controllers.pop();
  var top_controller = this.topController;
  // notify of upcoming change
  previous_controller._viewWillDisappear();
  previous_controller.viewWillDisappear();
  top_controller._viewWillAppear();
  top_controller.viewWillAppear();
  // add it to the tree
  this.view.appendChild(top_controller.view);
  // transition
  this.transitionToController(previous_controller, top_controller);
  //
  TKTransaction.commit();
};

/* ==================== Transition ==================== */

TKNavigationController.prototype.transitionToController = function (previous_controller, top_controller) {
  // mark that a transition is now in progress
  this.busy = true;
  // record some parameters that we will need at the end of the transition
  this.previousController = previous_controller;
  // figure out transitions
  if (previous_controller !== null) {
    if (IS_APPLE_TV && !previous_controller.enforcesCustomTransitions) {
      previous_controller.becomesInactiveTransition = TKViewTransitionDissolveOut;
    }
    previous_controller.view.applyTransition(previous_controller.becomesInactiveTransition, false);
  }
  if (IS_APPLE_TV && !top_controller.enforcesCustomTransitions) {
    top_controller.becomesActiveTransition = TKViewTransitionDissolveIn;
  }
  var top_controller_transition = top_controller.becomesActiveTransition;
  top_controller_transition.delegate = this;
  top_controller.view.applyTransition(top_controller_transition, false);
  //
  TKSpatialNavigationManager.sharedManager.managedController = top_controller;
  // track that we're moving from screen to screen
  window.dispatchEvent(TKUtils.createEvent('cursorwait', null));
};

TKNavigationController.prototype.transitionDidComplete = function (transition) {
  if (!this.busy) {
    return;
  }
  var top_controller = this.topController;
  // remove the old screen
  if (this.previousController !== null) {
    this.view.removeChild(this.previousController.view);
    this.previousController._viewDidDisappear();
    this.previousController.viewDidDisappear();
  }
  // notify of completed change
  top_controller._viewDidAppear();
  top_controller.viewDidAppear();
  // fire delegate saying we've moved to a new controller
  if (TKUtils.objectHasMethod(this.delegate, TKNavigationControllerDidShowController)) {
    this.delegate[TKNavigationControllerDidShowController](this, top_controller);
  }
  //
  this.busy = false;
  // pre-load screens that we can navigate to from here
  // for (var i = 0; i < top_controller.navigatesTo.length; i++) {
  //   var navigation_data = top_controller.navigatesTo[i];
  //   // pointer to the controller
  //   var controller = navigation_data.controller;
  //   // if it's a string, try to find it in the controllers hash
  //   if (TKUtils.objectIsString(controller)) {
  //     controller = TKController.controllers[controller];
  //   }
  //   // skip if we have an undefined object
  //   if (controller === undefined) {
  //     continue;
  //   }
  //   // otherwise, load it if it's not been loaded before
  //   if (controller._view === null) {
  //     controller.loadView();
  //   }
  // }
  // done moving from screen to screen
  window.dispatchEvent(TKUtils.createEvent('cursornormal', null));
};

TKClass(TKNavigationController);
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

const TKPageSliderControllerContainerCSSClass = 'tk-page-slider-controller-view';

TKPageSliderController.inherits = TKController;
TKPageSliderController.synthetizes = ['slidingViewData', 'pageControlData', 'previousPageButton', 'nextPageButton', 'highlightedPageIndex'];

/**
 *  @class
 *
 *  <p>A page slider controller adds the ability to browse through a collection of elements, often images, with nice and smooth transitions
 *  set up in CSS. Using this controller type, you can easily track when a new page is highlighted or activated. Optionally, you can also
 *  set up a series of indicators giving the user an overview of the number of images and arrows to navigate through elements, the connection
 *  between the various components being automatically handled behind the scenes for you.</p>
 *
 *  @extends TKController
 *  @since TuneKit 1.0
 *
 *  @param {Object} data A hash of properties to use as this object is initialized.
 */
function TKPageSliderController (data) {
  this._previousPageButton = null;
  this._nextPageButton = null;
  /**
   *  Indicates whether the pages managed by the controller are navigable with keys. Defaults to <code>true</code>.
   *  @type bool
   */
  this.highlightsFocusedPage = true;
  /**
   *  Indicates whether navigation of pages is done strictly with paging buttons. Defaults to <code>false</code>, allowing the Apple remote to
   *  be used to navigate between pages.
   *  @type bool
   */
  this.navigatesWithPagingButtonsOnly = false;
  /**
   *  Indicates whether the focused page can get activated. Defaults to <code>true</code>, setting this to <code>false</code> plays the limit sound when
   *  the user attempts to activate the focused page.
   *  @type bool
   */
  this.activatesFocusedPage = true;
  /**
   *  Provides the list of directions that the user can navigate out of the list of pages. By default, this array is empty, meaning that if the
   *  {@link #navigatesWithPagingButtonsOnly} property is set to <code>false</code> and pages can be navigated with arrow keys, then the user will not
   *  be able to move focus out of the pages from either ends. The directions allowed are the <code>TKSpatialNavigationManagerDirection</code> family
   *  of constants.
   *  @type Array
   */
  this.allowedOutwardNavigationDirections = [];
  // set up the sliding view
  /**
   *  The backing sliding view hosting the pages.
   *  @type TKSlidingView
   *  @private
   */
  this.slidingView = new TKSlidingView();
  this.slidingView.ready = false;
  this.slidingView.delegate = this;
  // set up the page control
  /**
   *  The backing page control hosting the page indicators.
   *  @type TKPageControl
   *  @private
   */
  this.pageControl = new TKPageControl();
  this.pageControl.delegate = this;
  //
  this._slidingViewData = null;
  this._pageControlData = null;
  //
  this.callSuper(data);
};

TKPageSliderController.prototype.processView = function () {
  this.callSuper();
  // restore properties that have not been set yet since construction
  this.restoreProperty('previousPageButton');
  this.restoreProperty('nextPageButton');
  this.restoreProperty('slidingViewData');
  this.restoreProperty('pageControlData');
  this.restoreProperty('highlightedPageIndex');
  // wire up actions if we have a previous and next button wired
  // add the sliding view and page control containers
  this.container = this._view.appendChild(document.createElement('div'));
  this.container.addClassName(TKPageSliderControllerContainerCSSClass);
  this.container.appendChild(this.slidingView.element);
  this.container.appendChild(this.pageControl.element);
  // ensure our first page gets told about its being highlighted
  this.pageWasHighlighted(this.highlightedPageIndex);
  this.syncPageButtons();
  // highlight the first page in case we have no explicit highlighted element
  if ((this.highlightedElement === null || !this.highlightedElement.isNavigable()) && this.slidingView.ready && this.highlightsFocusedPage) {
    this.highlightedElement = this.slidingView.activeElement;
  }
};

/**
 *  @name TKPageSliderController.prototype
 *  @property {int} highlightedPageIndex The index of the page currently selected within the collection of pages.
 */
TKPageSliderController.prototype.getHighlightedPageIndex = function () {
  return this.slidingView.activeElementIndex;
};

TKPageSliderController.prototype.setHighlightedPageIndex = function (index) {
  if (index === null) {
    return;
  }
  // apply to the sliding view if it's ready
  if (this.slidingView.ready) {
    this.slidingView.activeElementIndex = index;
    if (this.highlightedElement.hasClassName(TKSlidingViewCSSElementClass)) {
      this.registerNavigablePages();
      this.highlightedElement = this.slidingView.activeElement;
    }
  }
};

/**
 *  @name TKPageSliderController.prototype
 *  @property {String} previousPageButton A CSS selector matching a button to be used as the button to decrement the {@link #highlightedPageIndex}.
 */
TKPageSliderController.prototype.setPreviousPageButton = function (previousPageButton) {
  if (previousPageButton === null) {
    return;
  }
  // forget old button
  if (this._previousPageButton) {
    this.removeNavigableElement(this._previousPageButton);
  }
  // process new one
  if (previousPageButton !== null) {
    this._previousPageButton = this.view.querySelector(previousPageButton);
    if (this._previousPageButton !== null) {
      if (IS_APPLE_TV && !this.navigatesWithPagingButtonsOnly) {
        this._previousPageButton.style.display = 'none';
      }
      else {
        this.addNavigableElement(this._previousPageButton);
      }
    }
  }
};

/**
 *  @name TKPageSliderController.prototype
 *  @property {String} nextPageButton A CSS selector matching a button to be used as the button to increment the {@link #highlightedPageIndex}.
 */
TKPageSliderController.prototype.setNextPageButton = function (nextPageButton) {
  if (nextPageButton === null) {
    return;
  }
  // forget old button
  if (this._nextPageButton) {
    this.removeNavigableElement(this._nextPageButton);
  }
  // process new one
  if (nextPageButton !== null) {
    this._nextPageButton = this.view.querySelector(nextPageButton);
    if (this._nextPageButton !== null) {
      if (IS_APPLE_TV && !this.navigatesWithPagingButtonsOnly) {
        this._nextPageButton.style.display = 'none';
      }
      else {
        this.addNavigableElement(this._nextPageButton);
      }
    }
  }
};

/**
 *  @name TKPageSliderController.prototype
 *  @property {TKSlidingViewData} slidingViewData The set of properties used to set up the contents of the page slider.
 */
TKPageSliderController.prototype.setSlidingViewData = function (data) {
  if (data === null) {
    return;
  }
  // set up the data source if we have .elements on the data object
  if (!TKUtils.objectIsUndefined(data.elements)) {
    this.slidingView.dataSource = new TKSlidingViewDataSourceHelper(data.elements);
    delete data.element;
  }
  // see if we have some intersting bits to pass through
  var archived_page_index = this.getArchivedProperty('highlightedPageIndex');
  if (archived_page_index !== undefined) {
    data.activeElementIndex = archived_page_index;
  }
  // copy properties
  TKUtils.copyPropertiesFromSourceToTarget(data, this.slidingView);
  // init our view
  this.slidingView.init();
  //
  this.slidingView.ready = true;
  //
  this.syncPageButtons();
  // add the currently focused element to the list of keyboard elements and highlight it
  if (this.highlightsFocusedPage) {
    this.registerNavigablePages();
    this.highlightedElement = this.slidingView.activeElement;
    if (this.viewWasProcessed) {
      TKSpatialNavigationManager.sharedManager.highlightElement(this.slidingView.activeElement);
    }
  }
};

/**
 *  @name TKPageSliderController.prototype
 *  @property {TKPageControlData} pageControlData The set of properties used to set up the contents of the optional page indicators.
 */
TKPageSliderController.prototype.setPageControlData = function (data) {
  if (data === null) {
    return;
  }
  // set up the data source
  this.pageControl.dataSource = new TKPageControlDataSourceHelper(data);
  // copy properties
  TKUtils.copyPropertiesFromSourceToTarget(data, this.pageControl);
  // init our control
  this.pageControl.init();
  // get the current page from the sliding view if we have it set only after
  if (this.slidingView.ready) {
    this.pageControl.currentPage = this.highlightedPageIndex;
  }
};

/* ==================== Event Handling ==================== */

// private method meant to be over-ridden by a controller sub-classes to provide a custom element
// to highlight, returning null means there's nothing custom to report
TKPageSliderController.prototype._preferredElementToHighlightInDirection = function (currentElement, direction) {
  var can_exit_in_direction = (this.allowedOutwardNavigationDirections.indexOf(direction) != -1);
  var element = this.callSuper(currentElement, direction);
  if (!this.navigatesWithPagingButtonsOnly && currentElement.hasClassName(TKSlidingViewCSSElementClass)) {
    if (direction == KEYBOARD_LEFT) {
      if (this.slidingView.activeElementIndex <= 0 && !this.slidingView.loops) {
        if (!can_exit_in_direction) {
          element = null;
        }
      }
      else {
        element = this.slidingView.getElementAtIndex((this.slidingView.activeElementIndex + this.slidingView.numberOfElements - 1) % this.slidingView.numberOfElements);
      }
    }
    else if (direction == KEYBOARD_RIGHT) {
      if (this.slidingView.activeElementIndex >= this.slidingView.numberOfElements - 1 && !this.slidingView.loops) {
        if (!can_exit_in_direction) {
          element = null;
        }
      }
      else {
        element = this.slidingView.getElementAtIndex((this.slidingView.activeElementIndex + 1) % this.slidingView.numberOfElements);
      }
    }
  }
  return element;
};

TKPageSliderController.prototype.elementWasActivated = function (element) {
  // previous page button pressed
  if (element === this._previousPageButton) {
    var can_navigate = (this.slidingView.activeElementIndex > 0 || this.slidingView.loops);
    TKSpatialNavigationManager.soundToPlay = (can_navigate) ? SOUND_MOVED : SOUND_LIMIT;
    if (can_navigate) {
      this.unregisterNavigablePages();
    }
    this.slidingView.activeElementIndex--;
  }
  // next page button pressed
  else if (element === this._nextPageButton) {
    var can_navigate = (this.slidingView.activeElementIndex < this.slidingView.numberOfElements - 1 || this.slidingView.loops);
    TKSpatialNavigationManager.soundToPlay = (can_navigate) ? SOUND_MOVED : SOUND_LIMIT;
    if (can_navigate) {
      this.unregisterNavigablePages();
    }
    this.slidingView.activeElementIndex++;
  }
  // focused element in the sliding view
  else if (element.hasClassName(TKSlidingViewCSSFocusedClass)) {
    if (this.activatesFocusedPage) {
      this.pageWasSelected(this.slidingView.activeElementIndex);
    }
    else {
      TKSpatialNavigationManager.soundToPlay = SOUND_LIMIT;
    }
  }
  // fall back to default behavior
  else {
    this.callSuper(element);
  }
};

TKPageSliderController.prototype.elementWasHighlighted = function (element, previouslyHighlightedElement) {
  if (element.hasClassName(TKSlidingViewCSSElementClass)) {
    this.slidingView.activeElementIndex = element._slidingViewIndex;
    // track navigation on all elements if we're getting highlight for the first time
    if (previouslyHighlightedElement !== null &&
        (!previouslyHighlightedElement.hasClassName(TKSlidingViewCSSElementClass) ||
        previouslyHighlightedElement._controller !== this)) {
      this.registerNavigablePages();
    }
  }
};

TKPageSliderController.prototype.elementWasUnhighlighted = function (element, nextHighlightedElement) {
  // are we focusing an element outside of our sliding view?
  if (element.hasClassName(TKSlidingViewCSSElementClass) &&
      (!nextHighlightedElement.hasClassName(TKSlidingViewCSSElementClass) ||
      nextHighlightedElement._controller !== this)) {
    // make all the other elements non-navigable
    this.unregisterNavigablePages();
    // save for the active one
    this.addNavigableElement(this.slidingView.activeElement);
  }
};

TKPageSliderController.prototype.syncPageButtons = function () {
  // nothing to do if the sliding view is looping
  if (this.slidingView.loops || !this.isViewLoaded()) {
    return;
  }
  // check if the previous page button needs hiding
  if (this._previousPageButton instanceof Element) {
    this._previousPageButton[(this.slidingView.activeElementIndex <= 0 ? 'add' : 'remove') + 'ClassName']('inactive');
  }
  // check if the next page button needs hiding
  if (this._nextPageButton instanceof Element) {
    this._nextPageButton[(this.slidingView.activeElementIndex >= this.slidingView.numberOfElements - 1 ? 'add' : 'remove') + 'ClassName']('inactive');
  }
};

TKPageSliderController.prototype.registerNavigablePages = function () {
  if (this.navigatesWithPagingButtonsOnly) {
    this.addNavigableElement(this.slidingView.activeElement);
  }
  else {
    var elements = this.slidingView.element.querySelectorAll('.' + TKSlidingViewCSSElementClass);
    for (var i = 0; i < elements.length; i++) {
      this.addNavigableElement(elements[i]);
    }
  }
};

TKPageSliderController.prototype.unregisterNavigablePages = function () {
  var elements = this.slidingView.element.querySelectorAll('.' + TKSlidingViewCSSElementClass);
  for (var i = 0; i < elements.length; i++) {
    this.removeNavigableElement(elements[i]);
  }
};

/* ==================== TKSlidingView Protocol ==================== */

TKPageSliderController.prototype.slidingViewDidFocusElementAtIndex = function (view, index) {
  if (this.highlightsFocusedPage && this.slidingView.ready) {
    if (this.highlightedElement.hasClassName(TKSlidingViewCSSElementClass)) {
      this.registerNavigablePages();
    }
    else {
      this.unregisterNavigablePages();
      this.addNavigableElement(this.slidingView.activeElement);
    }
    // make sure the element has focus
    if (this.viewWasProcessed) {
      TKSpatialNavigationManager.sharedManager.highlightElement(this.slidingView.activeElement);
    }
  }
  //
  this.pageControl.currentPage = index;
  this.pageWasHighlighted(index);
  // update the states of previous and next buttons
  this.syncPageButtons();
};

TKPageSliderController.prototype.slidingViewDidBlurElementAtIndex = function (view, index) {
  if (this.highlightsFocusedPage) {
    this.unregisterNavigablePages();
  }
};

TKPageSliderController.prototype.slidingViewDidSelectActiveElement = function (view, index) {
  this.pageWasSelected(index);
};

TKPageSliderController.prototype.slidingViewStyleForItemAtIndex = function (view, index) {
  return this.styleForPageAtIndex(index);
};

TKPageSliderController.prototype.slidingViewDidHoverElementAtIndex = function (view, index) {
  this.pageWasHovered(index);
};

TKPageSliderController.prototype.slidingViewDidUnhoverElementAtIndex = function (view, index) {
  this.pageWasUnhovered(index);
};

/* ==================== Placeholder Methods ==================== */

/**
 *  Triggered as the {@link #highlightedPageIndex} property has changed when a new page became focused.
 *
 *  @param {int} index The index of the newly focused page
 */
TKPageSliderController.prototype.pageWasHighlighted = function (index) {};

/**
 *  Triggered as the focused page was selected by the user, either from clicking on the page or using the play/pause remote key.
 *
 *  @param {int} index The index of the activated page
 */
TKPageSliderController.prototype.pageWasSelected = function (index) {};

TKPageSliderController.prototype.pageWasHovered = function (index) {};

TKPageSliderController.prototype.pageWasUnhovered = function (index) {};

/**
 *  This method allows to provide custom style rules for a page programatically any time the {@link #highlightedPageIndex} property changes. The values in this
 *  array are expected to be individual two-value arrays, where the first index holds the CSS property name, and the second index its value.
 *
 *  @param {Array} index The index of the page for which we are trying to obtain custom styles.
 */
TKPageSliderController.prototype.styleForPageAtIndex = function (index) {
  return [];
};

/* ==================== TKPageControl Protocol ==================== */

TKPageSliderController.prototype.pageControlDidUpdateCurrentPage = function (control, newPageIndex) {
  this.slidingView.activeElementIndex = newPageIndex;
  this.pageControl.updateCurrentPageDisplay();
};

/* ==================== Archival ==================== */

TKPageSliderController.prototype.archive = function () {
  var archive = this.callSuper();
  archive.highlightedPageIndex = this.highlightedPageIndex;
  return archive;
};

TKClass(TKPageSliderController);
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

TKLyricsController.inherits = TKController;
TKLyricsController.synthetizes = ['currentSong', 'previousSongButton', 'nextSongButton'];

/**
 *  @class
 *
 *  <p>A lyrics controller is designed to make it easy to flip through a collection of lyrics. This controller type automatically wires the left and
 *  right keys to navigate between songs, and the author should leverage the {@link TKController#scrollableElement} property to identify the container
 *  for the scrolling lyrics region. Loading of new song content should be done using the {@link #songDidChange} method.</p>
 *
 *  @extends TKController
 *  @since TuneKit 1.0
 *
 *  @param {Object} data A hash of properties to use as this object is initialized.
 */
function TKLyricsController (data) {
  /**
   *  The number of songs that the controller will be flipping through.
   *  @type int
   */
  this.numberOfSongs = 0;
  this.defaultToFirstSong = false;
  this._currentSong = null;
  this._previousSongButton = null;
  this._nextSongButton = null;
  //
  this.callSuper(data);
};

/* ==================== View Processing ==================== */

TKLyricsController.prototype.processView = function () {
  this.callSuper();
  // restore properties that have not been set yet since construction
  this.restoreProperty('previousSongButton');
  this.restoreProperty('nextSongButton');
  this.restoreProperty('currentSong');
  // default to first song
  if (this.defaultToFirstSong && this._currentSong === null) {
    this.currentSong = 0;
  }
};

/* ==================== Keyboard Navigation ==================== */

TKLyricsController.prototype.wantsToHandleKey = function (key) {
  return (key == KEYBOARD_LEFT || key == KEYBOARD_RIGHT) ? true : this.callSuper(key);
};

TKLyricsController.prototype.keyWasPressed = function (key) {
  // default action is move, so wire that up
  TKSpatialNavigationManager.soundToPlay = SOUND_MOVED;
  // left should go to the previous song
  if (key == KEYBOARD_LEFT) {
    this.goToPreviousSong();
  }
  // right should go to the next song
  else if (key == KEYBOARD_RIGHT) {
    this.goToNextSong();
  }
  // let the default behavior happen too
  this.callSuper(key);
};

/* ==================== Previous / Next Buttons ==================== */

/**
 *  @name TKLyricsController.prototype
 *  @property {String} previousSongButton The CSS selector for the element acting as the trigger to navigate to the previous song.
 */
TKLyricsController.prototype.setPreviousSongButton = function (previousSongButton) {
  if (previousSongButton === null || IS_APPLE_TV) {
    return;
  }
  // forget old button
  if (this._previousSongButton) {
    this.removeNavigableElement(this._previousSongButton);
  }
  // process new one
  if (previousSongButton !== null) {
    this._previousSongButton = this.view.querySelector(previousSongButton);
    if (this._previousSongButton !== null) {
      this.addNavigableElement(this._previousSongButton);
    }
  }
};

/**
 *  @name TKLyricsController.prototype
 *  @property {String} nextSongButton The CSS selector for the element acting as the trigger to navigate to the next song.
 */
TKLyricsController.prototype.setNextSongButton = function (nextSongButton) {
  if (nextSongButton === null || IS_APPLE_TV) {
    return;
  }
  // forget old button
  if (this._nextSongButton) {
    this.removeNavigableElement(this._nextSongButton);
  }
  // process new one
  if (nextSongButton !== null) {
    this._nextSongButton = this.view.querySelector(nextSongButton);
    if (this._nextSongButton !== null) {
      this.addNavigableElement(this._nextSongButton);
    }
  }
};

TKLyricsController.prototype.elementWasActivated = function (element) {
  // previous page button pressed
  if (element === this._previousSongButton) {
    this.goToPreviousSong();
  }
  // next page button pressed
  else if (element === this._nextSongButton) {
    this.goToNextSong();
  }
  // fall back to default behavior
  else {
    this.callSuper(element);
  }
};

/* ==================== Page Navigation ==================== */

/**
 *  Shows the previous song.
 */
TKLyricsController.prototype.goToPreviousSong = function () {
  this.currentSong = ((this._currentSong + this.numberOfSongs) - 1) % this.numberOfSongs;
};

/**
 *  Shows the next song.
 */
TKLyricsController.prototype.goToNextSong = function () {
  this.currentSong = (this._currentSong + 1) % this.numberOfSongs;
};

/**
 *  @name TKLyricsController.prototype
 *  @property {int} currentSong The index of the current song. Whenever this value changes, the {@link #songDidChange} method is called.
 */
TKLyricsController.prototype.setCurrentSong = function (song) {
  if (song === null || song < 0 || song >= this.numberOfSongs) {
    return;
  }
  // track what song we're on
  this._currentSong = song;
  // let our instance know that we've moved to a new song
  this.songDidChange(song);
};

/**
 *  Triggered when a new song is displayed by the controller.
 */
TKLyricsController.prototype.songDidChange = function (song) {};

/* ==================== Archival ==================== */

TKLyricsController.prototype.archive = function () {
  var archive = this.callSuper();
  archive.currentSong = this.currentSong;
  return archive;
};

TKClass(TKLyricsController);
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

/**
 *  @class
 *  @name TKTabControllerDelegate
 *  @since TuneKit 1.0
 */

/**
 *  Indicates that a new controller is becoming the tab controller's selected controller and is about to become visible on screen.
 *
 *  @name tabControllerWillShowController
 *  @function
 *
 *  @param {TKTabController} tabController The tab controller.
 *  @param {TKController} controller The controller that is about to be shown by the tab controller.
 *  @memberOf TKTabControllerDelegate.prototype
 */
const TKTabControllerWillShowController = 'tabControllerWillShowController';  
/**
 *  Indicates that a new controller has become the tab controller's selected controller and is fully visible on screen.
 *
 *  @name tabControllerDidShowController
 *  @function
 *
 *  @param {TKTabController} tabController The tab controller.
 *  @param {TKController} controller The controller that is being shown by the tab controller.
 *  @memberOf TKTabControllerDelegate.prototype
 */
const TKTabControllerDidShowController = 'tabControllerDidShowController';  

/**
 *  The CSS class name applied to an element acting as a tab once it is the selected tab.
 *  @constant
 *  @type String
 */
const TKTabControllerSelectedCSSClass = 'tk-tab-selected';

TKTabController.inherits = TKController;
TKTabController.synthetizes = ['selectedController', 'selectedIndex', 'tabsSelector'];

/**
 *  @class
 *
 *  <p>A tab controller allows to bind a series of elements within the view, the tabs, to display each a given controller, the tab controller only
 *  allowing a single tab to be selected at once. Tabs are specified using the {@link #tabsSelector} CSS selector, and a controller for each tab needs to be
 *  stored in the {@link #controllers} array. By implementing the {@link TKTabControllerDelegate} protocol, a tab controller's {@link #delegate} can track as
 *  the user navigates between tabs. At any given time, the {@link #selectedController} property allows to find out which of the controllers is currently
 *  selected.</p>
 *
 *  @extends TKController
 *  @since TuneKit 1.0
 *
 *  @param {Object} data A hash of properties to use as this object is initialized.
 */
function TKTabController (data) {
  this._tabsSelector = null;
  this._selectedController = null;
  /**
   *  The controllers managed by this tab controller, ordered in the same way as the elements matched by {@link #tabsSelector} are.
   *  @type Array
   */
  this.controllers = [];
  this.tabs = [];
  /**
   *  The delegate for this tab controller, an object implementing the {@link TKTabControllerDelegate} protocol.
   *  @type Object
   */
  this.delegate = null;
  this.previousController = null;
  //
  this.busy = false;
  //
  this.callSuper(data);
};

/* ==================== Additional View Processing ==================== */

TKTabController.prototype.processView = function () {
  this.callSuper();
  //
  this.host = this._view.appendChild(document.createElement('div'));
  this.host.addClassName('tk-tab-contents');
  // restore properties that have not been set yet since construction
  this.restoreProperty('tabsSelector');
  this.restoreProperty('selectedIndex');
};

/* ==================== Synthetized Properties ==================== */

/**
 *  @name TKTabController.prototype
 *  @property {String} tabsSelector A CSS selector matching the elements within the controller's view that should act as triggers to display the matching 
 *  controller in the {@link #controllers} array.
 */
TKTabController.prototype.setTabsSelector = function (tabsSelector) {
  if (tabsSelector === null) {
    return;
  }
  // forget the old tabs
  for (var i = 0; i < this.tabs.length; i++) {
    var element = this.tabs[i];
    element._tabIndex = undefined;
    element._controller = undefined;
    this.removeNavigableElement(element);
  }
  // get the new tabs
  this._tabsSelector = tabsSelector;
  this.tabs = this._view.querySelectorAll(this._tabsSelector);
  // nothing to do if we don't have tabs
  if (this.tabs.length < 1) {
    return;
  }
  for (var i = 0; i < this.tabs.length; i++) {
    var tab = this.tabs[i];
    tab._tabIndex = i;
    tab._controller = this;
    this.addNavigableElement(tab);
  }
  // reset to the first tab, unless we have an archived one
  var archived_index = this.getArchivedProperty('selectedIndex');
  this.selectedIndex = (archived_index === undefined || archived_index < 0) ? 0 : archived_index;
};

/* ==================== Keyboard Handling ==================== */

TKTabController.prototype.getNavigableElements = function () {
  return this._navigableElements.concat(this.selectedController.navigableElements);
};

TKTabController.prototype.handleEvent = function (event) {
  this.callSuper(event);
  //
  if (event.currentTarget._tabIndex !== undefined) {
    if (event.type == 'highlight') {
      this.selectedIndex = event.currentTarget._tabIndex;
    }
  }
};

TKTabController.prototype.elementWasActivated = function (element) {
  this.callSuper(element);
  // tab was activated
  if (element._tabIndex !== undefined) {
    // highlight in case we weren't already
    if (this.highlightedElement !== element) {
      TKSpatialNavigationManager.sharedManager.highlightElement(element);
    }
    // notify we were activated
    else {
      this.tabAtIndexWasActivated(element._tabIndex);
    }
  }
};

/**
 *  Indicates that a new tab has been activated at the given index.
 *
 *  @param {int} index The index for the tab that was just activated.
 */
TKTabController.prototype.tabAtIndexWasActivated = function (index) {};

/* ==================== Controllers ==================== */

/**
 *  @name TKTabController.prototype
 *  @property {int} selectedIndex The index of the selected tab.
 */
TKTabController.prototype.getSelectedIndex = function () {
  return (this._selectedController === null) ? -1 : this.controllers.indexOf(this._selectedController);
};

TKTabController.prototype.setSelectedIndex = function (index) {
  var selected_index = this.selectedIndex;
  if (index !== selected_index && index >= 0 && index < this.controllers.length) {
    // move to the new controller
    this.selectedController = this.controllers[index];
  }
};

/**
 *  @name TKTabController.prototype
 *  @property {TKController} selectedController The selected controller.
 */
TKTabController.prototype.setSelectedController = function (controller) {
  var selected_index = this.controllers.indexOf(controller);
  // do nothing if we don't know about such a controller, or we're already on this controller
  if (controller === this._selectedController || selected_index == -1) {
    return;
  }
  // clean up before starting a new transition
  if (this.busy) {
    this.transitionDidComplete(null);
  }
  //
  TKTransaction.begin();
  // mark that a transition is now in progress
  this.busy = true;
  // get pointers to object we'll manipulate
  var previous_controller = this._selectedController;
  var next_view = controller.view;
  // fire delegate saying we're moving to a new controller
  if (TKUtils.objectHasMethod(this.delegate, TKTabControllerWillShowController)) {
    this.delegate[TKTabControllerWillShowController](this, controller);
  }
  // track this is our newly selected controller
  this._selectedController = controller;
  // notify of upcoming change and update tabs styling
  if (previous_controller !== null) {
    previous_controller._viewWillDisappear();
    previous_controller.viewWillDisappear();
  }
  controller._viewWillAppear();
  controller.viewWillAppear();
  // add it to the tree
  this.host.appendChild(controller.view);
  // transition
  var manager = TKSpatialNavigationManager.sharedManager;
  if (previous_controller !== null) {
    // unregister the old controller
    previous_controller.parentController = null;
    manager.unregisterController(previous_controller);
    // remove the selected CSS class from the previous tab, if any
    this.tabs[this.controllers.indexOf(previous_controller)].removeClassName(TKTabControllerSelectedCSSClass);
    this.transitionToController(previous_controller, controller);
  }
  else {
    this.busy = true;
    this.transitionDidComplete();
    // highlight the element
    if (this.highlightedElement === null) {
      this.highlightedElement = this.tabs[this.selectedIndex]
    }
  }
  // add the selected CSS class to the new controller's tab
  this.tabs[selected_index].addClassName(TKTabControllerSelectedCSSClass)
  // also ensure that element has highlight
  manager.highlightElement(this.tabs[selected_index]);
  // and that the new controller is registered for navigation
  controller.parentController = this;
  manager.registerController(controller);
  //
  TKTransaction.commit();
};

/* ==================== Transition ==================== */

TKTabController.prototype.transitionToController = function (previous_controller, top_controller) {
  // record some parameters that we will need at the end of the transition
  this.previousController = previous_controller;
  // figure out transitions
  if (previous_controller !== null) {
    previous_controller.view.applyTransition(previous_controller.becomesInactiveTransition, false);
  }
  var top_controller_transition = top_controller.becomesActiveTransition;
  top_controller_transition.delegate = this;
  top_controller.view.applyTransition(top_controller_transition, false);
};

TKTabController.prototype.transitionDidComplete = function (transition) {
  // update the highlightable items and notify of completed change
  if (this.previousController !== null) {
    if (this.previousController.view.parentNode === this.host) {
      this.host.removeChild(this.previousController.view);
    }
    this.previousController._viewDidDisappear();
    this.previousController.viewDidDisappear();
  }
  this._selectedController._viewDidAppear();
  this._selectedController.viewDidAppear();
  // fire delegate saying we've moved to a new controller
  if (TKUtils.objectHasMethod(this.delegate, TKTabControllerDidShowController)) {
    this.delegate[TKTabControllerDidShowController](this, this._selectedController);
  }
  // not busy anymore
  this.busy = false;
};

/* ==================== Archival ==================== */

TKTabController.prototype.archive = function () {
  var archive = this.callSuper();
  archive.selectedIndex = this.selectedIndex;
  return archive;
};

TKClass(TKTabController);
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

const TKSlideshowControllerContainerCSSClass = 'tk-slideshow-controller-view';

TKSlideshowController.inherits = TKController;
TKSlideshowController.synthetizes = ['slidingViewData', 'togglePlaybackButton', 'playing', 'currentSlideIndex', 'numberOfSlides', 'previousSlideButton', 'nextSlideButton'];

/**
 *  @class
 *
 *  <p>A slideshow controller plays through a collection of slides, also allowing to control the playback state and position of the slideshow. Control
 *  buttons are easily wired and remote-based navigation is completely automated.</p>
 *
 *  @extends TKController
 *  @since TuneKit 1.0
 *
 *  @param {Object} data A hash of properties to use as this object is initialized.
 */
function TKSlideshowController (data) {
  // public properties
  this._slidingViewData = null;
  this._togglePlaybackButton = null;
  this._previousSlideButton = null;
  this._nextSlideButton = null;
  this._playing = null;
  /**
   *  Indicates whether the slideshow loops through for constant playback. Defaults to <code>true</code>.
   *  @type bool
   */
  this.loops = true;
  /**
   *  Indicates the duration in milliseconds each slide remains on screen.
   *  @type int
   */
  this.interval = 3000;
  this.timer = null;
  this.willNeedToResume = true;
  // set up the sliding view
  this.slidingView = new TKSlidingView();
  this.slidingView.ready = false;
  this.slidingView.delegate = this;
  //
  this.callSuper(data);
};

/* ==================== View Processing ==================== */

TKSlideshowController.prototype.processView = function () {
  this.callSuper();
  // restore properties that have not been set yet since construction
  this.restoreProperty('slidingViewData');
  this.restoreProperty('previousSlideButton');
  this.restoreProperty('nextSlideButton');
  this.restoreProperty('togglePlaybackButton');
  this.restoreProperty('currentSlideIndex');
  this.restoreProperty('playing');
  // add the sliding view and slide control containers
  this.container = this._view.appendChild(document.createElement('div'));
  this.container.addClassName(TKSlideshowControllerContainerCSSClass);
  this.container.appendChild(this.slidingView.element);
  // ensure our first slide gets told about its being highlighted
  this.slideDidChange(this.currentSlideIndex);
  // start playing by default
  if (this._playing === null) {
    this.willNeedToResume = true;
  }
};

TKSlideshowController.prototype._viewDidAppear = function () {
  if (this.willNeedToResume) {
    this.playing = true;
  }
};

TKSlideshowController.prototype._viewWillDisappear = function () {
  this.willNeedToResume = this.playing;
  this.playing = false;
};

/* ==================== Synthetized Properties ==================== */

/**
 *  @name TKSlideshowController.prototype
 *  @property {bool} playing Indicates the current playback state of the slideshow, defaults to <code>true</code>.
 */
TKSlideshowController.prototype.setPlaying = function (playing) {
  if (this._playing == playing) {
    return;
  }
  // pause
  if (!playing) {
    window.clearTimeout(this.timer);
  }
  // resume
  else {
    this.rewindTimer();
  }
  // remember ivar
  this._playing = playing;
  // inform the playback state changed
  this.playbackStateDidChange();
};

/**
 *  @name TKSlideshowController.prototype
 *  @property {int} numberOfSlides Indicates how many slides total are in the slideshow.
 */
TKSlideshowController.prototype.getNumberOfSlides = function () {
  return (!this.slidingView.ready) ? 0 : this.slidingView.numberOfElements;
};

/**
 *  @name TKSlideshowController.prototype
 *  @property {int} currentSlideIndex Indicates the index of the current slide.
 */
TKSlideshowController.prototype.getCurrentSlideIndex = function () {
  return this.slidingView.activeElementIndex;
};

TKSlideshowController.prototype.setCurrentSlideIndex = function (index) {
  if (index === null || !this.slidingView.ready) {
    return;
  }
  // out of range
  if (index < 0 || index >= this.numberOfSlides) {
    return;
  }
  // update the slideshow index
  this.slidingView.activeElementIndex = index;
  // update timers if we're running
  if (this.playing) {
    // cancel the previous timer in case we still had one running
    window.clearTimeout(this.timer);
    // rewind it, and set playback to false in case we can't rewind any further
    if (!this.rewindTimer()) {
      this.playing = false;
    }
  }
};

/**
 *  @name TKSlideshowController.prototype
 *  @property {String} togglePlaybackButton A CSS selector matching a button to be used as the button to control the playback state.
 */
TKSlideshowController.prototype.setTogglePlaybackButton = function (togglePlaybackButton) {
  if (togglePlaybackButton === null) {
    return;
  }
  // forget old button
  if (this._togglePlaybackButton) {
    this._togglePlaybackButton.removeEventListener('click', this, false);
  }
  // process new one
  this._togglePlaybackButton = this.view.querySelector(togglePlaybackButton);
  if (this._togglePlaybackButton !== null) {
    if (IS_APPLE_TV) {
      this._togglePlaybackButton.style.display = 'none';
    }
    else {
      this._togglePlaybackButton.addEventListener('click', this, false);
    }
  }
};

/**
 *  @name TKSlideshowController.prototype
 *  @property {String} previousSlideButton A CSS selector matching a button to be used as the button to decrement the {@link #currentSlideIndex}.
 */
TKSlideshowController.prototype.setPreviousSlideButton = function (previousSlideButton) {
  if (previousSlideButton === null) {
    return;
  }
  // forget old button
  if (this._previousSlideButton) {
    this._previousSlideButton.removeEventListener('click', this, false);
  }
  // process new one
  this._previousSlideButton = this.view.querySelector(previousSlideButton);
  if (this._previousSlideButton !== null) {
    if (IS_APPLE_TV) {
      this._previousSlideButton.style.display = 'none';
    }
    else {
      this._previousSlideButton.addEventListener('click', this, false);
    }
  }
};

/**
 *  @name TKSlideshowController.prototype
 *  @property {String} nextSlideButton A CSS selector matching a button to be used as the button to increment the {@link #currentSlideIndex}.
 */
TKSlideshowController.prototype.setNextSlideButton = function (nextSlideButton) {
  if (nextSlideButton === null) {
    return;
  }
  // forget old button
  if (this._nextSlideButton) {
    this._nextSlideButton.removeEventListener('click', this, false);
  }
  // process new one
  this._nextSlideButton = this.view.querySelector(nextSlideButton);
  if (this._nextSlideButton !== null) {
    if (IS_APPLE_TV) {
      this._nextSlideButton.style.display = 'none';
    }
    else {
      this._nextSlideButton.addEventListener('click', this, false);
    }
  }
};

/**
 *  @name TKSlideshowController.prototype
 *  @property {TKSlidingViewData} slidingViewData The set of properties used to set up the contents of the page slider.
 */
TKSlideshowController.prototype.setSlidingViewData = function (data) {
  if (data === null) {
    return;
  }
  // set up the data source if we have .elements on the data object
  if (!TKUtils.objectIsUndefined(data.elements)) {
    this.slidingView.dataSource = new TKSlidingViewDataSourceHelper(data.elements);
    delete data.element;
  }
  // see if we have some intersting bits to pass through
  var archived_slide_index = this.getArchivedProperty('currentSlideIndex');
  if (archived_slide_index !== undefined) {
    data.activeElementIndex = archived_slide_index;
  }
  // copy properties
  TKUtils.copyPropertiesFromSourceToTarget(data, this.slidingView);
  // init our view
  this.slidingView.init();
  //
  this.slidingView.ready = true;
};

/* ==================== Previous / Next Slide ==================== */

TKSlideshowController.prototype.attemptToGoToPreviousSlide = function () {
  if (!this.loops && this.currentSlideIndex <= 0) {
    TKSpatialNavigationManager.soundToPlay = SOUND_LIMIT;
  }
  else {
    this.goToPreviousSlide();
  }
};

TKSlideshowController.prototype.attemptToGoToNextSlide = function () {
  if (!this.loops && this.currentSlideIndex >= this.numberOfSlides - 1) {
    TKSpatialNavigationManager.soundToPlay = SOUND_LIMIT;
  }
  else {
    this.goToNextSlide();
  }
};

TKSlideshowController.prototype.goToPreviousSlide = function () {
  this.currentSlideIndex = ((this.currentSlideIndex + this.numberOfSlides) - 1) % this.numberOfSlides;
};

TKSlideshowController.prototype.goToNextSlide = function () {
  this.currentSlideIndex = (this.currentSlideIndex + 1) % this.numberOfSlides;
};

TKSlideshowController.prototype.rewindTimer = function () {
  if (this.loops || this.currentSlideIndex < this.numberOfSlides - 1) {
    var _this = this;
    this.timer = window.setTimeout(function () {
      _this.goToNextSlide();
    }, this.interval);
    return true;
  }
  else {
    return false;
  }
};

/* ==================== Keyboard Navigation ==================== */

TKSlideshowController.prototype.wantsToHandleKey = function (key) {
  return (key == KEYBOARD_LEFT || key == KEYBOARD_RIGHT || key == KEYBOARD_RETURN) ? true : this.callSuper(key);
};

TKSlideshowController.prototype.keyWasPressed = function (key) {
  // default action is move, so wire that up
  TKSpatialNavigationManager.soundToPlay = SOUND_MOVED;
  // left should go to the previous slide
  if (key == KEYBOARD_LEFT) {
    this.attemptToGoToPreviousSlide();
  }
  // right should go to the next slide
  else if (key == KEYBOARD_RIGHT) {
    this.attemptToGoToNextSlide();
  }
  // return key should toggle playback
  else if (key == KEYBOARD_RETURN) {
    TKSpatialNavigationManager.soundToPlay = SOUND_ACTIVATED;
    this.playing = !this.playing;
  }
  // let the default behavior happen too
  this.callSuper(key);
};

TKSlideshowController.prototype.elementWasActivated = function (element) {
  // toggle playback button pressed
  if (element === this._togglePlaybackButton) {
    this.playing = !this.playing;
  }
  // previous slide button pressed
  else if (element === this._previousSlideButton) {
    this.attemptToGoToPreviousSlide();
  }
  // next slide button pressed
  else if (element === this._nextSlideButton) {
    this.attemptToGoToNextSlide();
  }
  // fall back to default behavior
  else {
    this.callSuper(element);
  }
};

/* ==================== TKSlidingView Protocol ==================== */

TKSlideshowController.prototype.slidingViewDidFocusElementAtIndex = function (view, index) {
  this.slideDidChange(index);
};

TKSlideshowController.prototype.slidingViewStyleForItemAtIndex = function (view, index) {
  return this.styleForSlideAtIndex(index);
};

/* ==================== Placeholder Methods ==================== */

/**
 *  Triggered when the playback state has changed.
 */
TKSlideshowController.prototype.playbackStateDidChange = function () {};

/**
 *  Triggered when the {@link #currentSlideIndex} property has changed.
 *
 *  @param {int} index The index of the current slide.
 */
TKSlideshowController.prototype.slideDidChange = function (index) {};

/**
 *  This method allows to provide custom style rules for a slide programatically any time the {@link #currentSlideIndex} property changes. The values in this
 *  array are expected to be individual two-value arrays, where the first index holds the CSS property name, and the second index its value.
 *
 *  @param {Array} index The index of the slide for which we are trying to obtain custom styles.
 */
TKSlideshowController.prototype.styleForSlideAtIndex = function (index) {
  return [];
};

/* ==================== Archival ==================== */

TKSlideshowController.prototype.archive = function () {
  var archive = this.callSuper();
  archive.currentSlideIndex = this.currentSlideIndex;
  return archive;
};

TKClass(TKSlideshowController);
/*
 *  Copyright © 2009 Apple Inc. All rights reserved.
 */

// XXX: this should be set dynamically as needed
const ARCHIVES_AND_RESTORES = false;
 
var bookletController = new TKObject();

bookletController.init = function () {
  // stop current playback
  window.iTunes.stop();
  
  // set up audio loop
  this.startAudioLoop();
  
  // determine play position if this a movie
  if (appData.feature.XID){
    appData.feature.trackObj = this.getTrack(appData.feature);
    if (appData.feature.trackObj && appData.feature.trackObj.bookmark != 0){
      this.dispatchDisplayUpdates();
    }
  }
  
  // add event listeners
  window.addEventListener("play", this, false);
  window.addEventListener("pause", this, false);
  window.addEventListener("videoclosed", this, false);
  window.addEventListener("unload", this, false);

  // check if we have an archive to restore from
  this.restoreFromJSON();

  // create our navigation controller and add the home controller as the root controller
  this.navigation = new TKNavigationController({
    id : 'navigation',
    rootController : homeController,
    delegate : this
  });
};

bookletController.archiveToJSON = function () {
  if (!ARCHIVES_AND_RESTORES) {
    return;
  }
  //
  var archive = {
    controllers: {}
  };
  // first, get the navigation stack of controllers
  var controllers_stack_IDs = [];
  for (var i = 0; i < this.navigation.controllers.length; i++) {
    controllers_stack_IDs.push(this.navigation.controllers[i].id);
  }
  archive.navigationStack = controllers_stack_IDs;
  // then archive all known controllers that aren't the navigation stack
  for (var i in TKController.controllers) {
    if (i == 'navigation') {
      continue;
    }
    archive.controllers[i] = TKController.controllers[i].archive();
  }
  // archive is complete, now save it to disk
  window.localStorage.archive = JSON.stringify(archive);
};

bookletController.restoreFromJSON = function () {
  if (!ARCHIVES_AND_RESTORES) {
    return;
  }
  // check if we have an archive to restore from
  var json_archive = window.localStorage.archive;
  if (json_archive === undefined) {
    return;
  }
  // parse the JSON archive into a JS object that we track at all times
  this.archive = JSON.parse(json_archive);
};

bookletController.handleEvent = function(event) {
  switch (event.type) {
    case "play":
      // video has started to play - stop the audio loop
      this.stopAudioLoop();
      //this.dispatchDisplayUpdates();
      break;
    case "pause":
      // video has paused
      //this.dispatchDisplayUpdates();
      break;
    case "videoclosed":
      // video has stopped - restart audio loop
      this.startAudioLoop();
      this.dispatchDisplayUpdates();
      
      // stub to check what chapter we are on for sticky chapters
      debug(iTunes.currentChapter);
      break;
    case "unload":
      // archive our state
      this.archiveToJSON();
      break;
    default:
      debug("Unknown event type in bookletController : " + event.type);
  }
};

bookletController.startAudioLoop = function() {

  // if the loop exists already, we're being asked to resume
  // check if we're set to do so, and if not, exit without starting playback
  if (this.audioLoop && appData.audioLoop && !appData.audioLoop.loop) {
    this.audioLoop.pause();
    this.audioLoop.volume = 0;
    return;
  }
  
  // create the loop if it doesn't exist yet
  if (appData.audioLoop && !this.audioLoop) {
    this.audioLoop = new Audio();
    this.audioLoop.src = appData.audioLoop.src;
    // make sure this background audio is never displayed
    this.audioLoop.style.display = "none";
    // add it to the document so that iTunes will notice it is there
    document.body.appendChild(this.audioLoop);
    this.audioLoop.volume = 0;
  }
  
  if (this.audioLoop) {
    this.audioLoop.loop = appData.audioLoop.loop;
    this.audioLoop.volume = Math.min(1, window.iTunes.volume);
    this.audioLoop.play();
  }
};

bookletController.stopAudioLoop = function() {
  if (this.audioLoop) {
    this.audioLoop.pause();
    this.audioLoop.loop = false;
    this.audioLoop.currentTime = 0; // reset to beginning
  }
};

bookletController.playbackHasStarted = function (){
  return (this.trackBookmark(appData.feature) == 0) ? false : true;    
}

bookletController.play = function (trackObj) {
  var track = this.getTrack(trackObj);
  
  if (track != null){
    iTunes.stop();
    track.play();
  }
};

bookletController.playFeature = function (){
  bookletController.play(appData.feature);
};

bookletController.resumeFeature = function(){
  bookletController.playFeature();
};

bookletController.playChapter = function (index){
  iTunes.stop();
  if (appData.feature.trackObj != null){
    appData.feature.trackObj.play({startChapterIndex : index});
  }
};

bookletController.getChapter = function (){
  if (appData.feature.trackObj && appData.feature.trackObj.chapters){
    if ((iTunes.currentChapter == 0 && appData.feature.trackObj.bookmark != 0) || IS_APPLE_TV){
      var estimatedChapter = Math.floor((appData.feature.trackObj.bookmark /  appData.feature.trackObj.duration) *  appData.feature.trackObj.chapters.length);
      var actualChapter = -1;

      if ((appData.feature.trackObj.chapters[estimatedChapter].startOffsetTime / 1000) == appData.feature.trackObj.bookmark){
      } else if ((appData.feature.trackObj.chapters[estimatedChapter].startOffsetTime / 1000) < appData.feature.trackObj.bookmark){
        while (estimatedChapter < appData.feature.trackObj.chapters.length && (appData.feature.trackObj.chapters[estimatedChapter].startOffsetTime / 1000) < appData.feature.trackObj.bookmark){
          estimatedChapter++;
        }
      } else if ((appData.feature.trackObj.chapters[estimatedChapter].startOffsetTime / 1000) > appData.feature.trackObj.bookmark){
        while (estimatedChapter >= 0 && (appData.feature.trackObj.chapters[estimatedChapter].startOffsetTime / 1000) > appData.feature.trackObj.bookmark){
          estimatedChapter--;
        }
      }
      actualChapter = estimatedChapter;
      debug("GET CHAPTER: estimating: " + actualChapter);
      return actualChapter;
    } else {
      debug("GET CHAPTER: itunes query: " + iTunes.currentChapter);
      return iTunes.currentChapter;
    }
  } else {
    return -1;
  }
}

bookletController.buildPlaylist = function (tracks){
  var tracklistObj = iTunes.createTempPlaylist();
  var tracklist = [];
  
  for (var i = 0; i < tracks.length; i++){
    var track = this.getTrack(tracks[i]);
    if (track != null){
      tracklist.push(track);
    }
  }
  
  tracklistObj.addTracks(tracklist);
  debug("added " + tracklist.length + " of " + tracks.length + " tracks successfully.");
  return tracklistObj;
};

bookletController.buildNonLibraryPlaylist = function (tracks){
  var tracklistObj = iTunes.createTempPlaylist();
  var tracklist = [];
  
  for (var i = 0; i < tracks.length; i++){
    var track = {};
    track.url = "videos/" + tracks[i].src;
    track.title = tracks[i].string;
    track.artist = appData.feature.artist;
    track.album = appData.feature.title;
    debug("adding: " + track.title + " (" + track.url + ")");
    tracklist.push(track);
  }
  
  debug("pushing to tracklistOb");
  tracklistObj.addURLs(tracklist);
  return tracklistObj;
};

bookletController.trackDuration = function (trackObj){
  var track = this.getTrack(trackObj);
  if (track != null){
    debug("querying duration");
    return track.durationAsString;
  } else {
    return "0:00";
  }
};

bookletController.trackNumber = function (trackObj){
  var track = this.getTrack(trackObj);
  if (track != null){
    debug("querying track number");
    return track.trackNumber;
  } else {
    return "0";
  }
};

bookletController.trackBookmark = function (trackObj){
  var track = this.getTrack(trackObj);
  if (track != null){
    debug("querying bookmark");
    return track.bookmark;
  } else {
    return "0";
  }
};

bookletController.getTrack = function (trackObj){
  if (trackObj.XID){
    debug("searching by XID: " + trackObj.XID);
    var iTunesTrack = window.iTunes.findTracksByXID(trackObj.XID);
    if (iTunesTrack.length > 0){
      debug("found by XID");
      return iTunesTrack[0];
    } else {
      debug("XID not found in library");
      return null;
    }
  } else {
    debug("no XID");
    return null;
  }
};

bookletController.playNonLibraryContent = function (trackObj){
  debug("videos/" + trackObj.src);
  debug({title : trackObj.string, artist : appData.feature.artist, album : appData.feature.title});
  window.iTunes.play("videos/" + trackObj.src, {title : trackObj.string, artist : appData.feature.artist, album : appData.feature.title});
};

bookletController.childControllers = [];

bookletController.registerForDisplayUpdates = function (childController) {
  if (this.childControllers.indexOf(childController) == -1) {
    this.childControllers.push(childController);
  }
};

bookletController.dispatchDisplayUpdates = function () {
  for (var i=0; i < this.childControllers.length; i++) {
    if (TKUtils.objectIsFunction(this.childControllers[i].updateDisplay)) {
      this.childControllers[i].updateDisplay();
    }
  }
};

/* ================= iTunes Emulation ======================== */

var iTunesEmulator = {
  volume : 1,
  platform : 'Emulator',
  version : '-1'
};

iTunesEmulator.play = function (mediaLocation) {
  debug("iTunesEmulator - play: " + mediaLocation);
};

iTunesEmulator.stop = function () {
  debug("iTunesEmulator - stop");
};

iTunesEmulator.findTracksByStoreID = function (storeID) {
  debug("iTunesEmulator - findTracksByStoreID: " + storeID);
  return [new ITunesTrackEmulator()];
};

iTunesEmulator.findTracksByXID = function (xID) {
  debug("iTunesEmulator - findTracksByXID: " + xID);
  return [new ITunesTrackEmulator()];
};

iTunesEmulator.createTempPlaylist = function () {
  return {
    tracks: [],
    addTracks: function () {}
  };
};

function ITunesTrackEmulator() {
}

ITunesTrackEmulator.prototype.play = function (params) {
  debug("iTunesTrackEmulator - play: " + params);
  // fake the play event to the window
  var event = document.createEvent("HTMLEvents");
  event.initEvent("play", false, false);
  window.dispatchEvent(event);
  setTimeout(function() {
    debug("iTunesTrackEmulator - coming back from playback");
    event = document.createEvent("HTMLEvents");
    event.initEvent("videoclosed", false, false);
    window.dispatchEvent(event);
  }, 5000);
};

/* ================= Initialisation ======================== */

window.addEventListener('load', function () {
  // override select start
  document.onselectstart = function() { return false; };
  // check for iTunes object, create a dummy if it doesn't exist
  if (!window.iTunes) {
    window.iTunes = iTunesEmulator;
  }
  // init the booklet controller
  bookletController.init();
}, false);
