 function alphabetPosition(text) {
   text = text.toLowerCase();
   var acode = 'a'.charCodeAt(0);
   var s = "";
   for(var i = 0; i < text.length; i++){
     if ('a' <= text[i] && text[i] <= 'z'){
       idx = (text[i].charCodeAt(0) - acode) + 1;
       s += ((s === "") ? "" : " ") + idx.toString();
     }
   }
   return s;
 }
