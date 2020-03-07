open! Core_kernel;
open Option;
open Incr_dom;

// Left to right composition
let (%>) = (f1: 'a => 'x, f2: 'x => 'b, x: 'a): 'b => f2(f1(x));

let sanitise_classname = className =>
  if (String.contains(className, ' ')) {
    Vdom.Attr.classes(Core_kernel.String.split(className, ~on=' '));
  } else {
    Vdom.Attr.class_(className);
  };

let maybe_apply = (~validator=Option.some, converter, value) => {
    value >>= validator >>| converter
}

let no_empty = item =>
  if (String.length(item) == 0) {
    None;
  } else {
    Some(item);
  };

let ariaHiddenProperty = Vdom.Attr.bool_property("aria-hidden");
let keyProperty = Js_of_ocaml.Js.Unsafe.inject %> Vdom.Attr.property("key");

let genericElement =
    (
      creator,
      ~type_=?,
      ~id=?,
      ~className=?,
      ~onClick=?,
      ~ariaHidden: option(bool)=?,
      ~key: option(int)=?,
      ~children,
      _: unit,
    ) => {
  let attrs = [
    maybe_apply(~validator=no_empty, sanitise_classname, className),
    maybe_apply(
      ariaHiddenProperty,
      ariaHidden,
    ),
    maybe_apply(
      keyProperty,
      key,
    ),
    maybe_apply(Vdom.Attr.on_click, onClick),
    maybe_apply(Vdom.Attr.id, id),
    maybe_apply(Vdom.Attr.type_, type_),
  ];

  let filtered = List.filter_opt(attrs);

  creator(filtered, children);
};

let body = genericElement(Vdom.Node.body);
let div = genericElement(Vdom.Node.div);
let h1 = genericElement(Vdom.Node.h1);
let tr = genericElement(Vdom.Node.tr);
let td = genericElement(Vdom.Node.td);
let a = genericElement(Vdom.Node.a);
let span = genericElement(Vdom.Node.span);
let button = genericElement(Vdom.Node.button);
let tbody = genericElement(Vdom.Node.tbody);
let table = genericElement(Vdom.Node.table);
