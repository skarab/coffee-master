function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6373\" class=\"headerLeftMenuInActive\"><a id=\"aID6373\" href=\"#\" OnMouseOver=\"link('_dir','geometric0',this)\" class=\"leftMenuLinkHeadInActive\">geometric</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID880\" class=\"leftMenuInActive\"><a id=\"aID880\" href=\"#\" OnMouseOver=\"link('_class','GeometricRenderer54809',this)\" class=\"leftMenuLinkInActive\">GeometricRenderer</a></div>\n");
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
