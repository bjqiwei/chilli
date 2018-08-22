Array.prototype.remove=function(value){
 
 for(var i=0;i<this.length;i++)
 {
  //alert(i);
  if(this[i] == value){
	for(var rindex = i; rindex< this.length;rindex++){
		//alert("remove:" + rindex);
		this[rindex]= rindex+1 <this.length? this[rindex+1]:null; 
	}
	this.length = this.length-1;
	return value;
  }
  
 }
 return ;
}