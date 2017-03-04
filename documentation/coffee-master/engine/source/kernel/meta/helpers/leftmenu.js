function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6303\" class=\"headerLeftMenuInActive\"><a id=\"aID6303\" href=\"#\" OnMouseOver=\"link('_dir','helpers0',this)\" class=\"leftMenuLinkHeadInActive\">helpers</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID770\" class=\"leftMenuInActive\"><a id=\"aID770\" href=\"#\" OnMouseOver=\"link('_class','ObjectPointer53261',this)\" class=\"leftMenuLinkInActive\">ObjectPointer</a></div>\n");
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
