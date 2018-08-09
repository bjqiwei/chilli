Object.prototype.empty=function(){
 
 for(var i in this)
 {
  if(i !== 'empty')
     return false;
 }
  
 return true;
}