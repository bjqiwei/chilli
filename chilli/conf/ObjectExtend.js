
Object.prototype.size=function(){
 
 var count = 0;
 for(var pro in this)
 {
   if(this.hasOwnProperty(pro)) { // 这里扩展了对象,所以必须判断
     count++;
   }
 }
  
  return count;
}

Object.prototype.empty=function(){
  return this.size() == 0;
}


Object.prototype.get = function(index) {
	
 var count = -1;
 for(var pro in this)
 {
   if(this.hasOwnProperty(pro)) { // 这里扩展了对象,所以必须判断
     count++;
   }
   
   if(count == index)
	   return pro;
   
 }

}
