function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6379\" class=\"headerLeftMenuInActive\"><a id=\"aID6379\" href=\"#\" OnMouseOver=\"link('_dir','state0',this)\" class=\"leftMenuLinkHeadInActive\">state</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID887\" class=\"leftMenuInActive\"><a id=\"aID887\" href=\"#\" OnMouseOver=\"link('_class','RenderState54809',this)\" class=\"leftMenuLinkInActive\">RenderState</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
