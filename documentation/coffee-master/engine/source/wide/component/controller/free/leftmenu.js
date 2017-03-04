function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6418\" class=\"headerLeftMenuInActive\"><a id=\"aID6418\" href=\"#\" OnMouseOver=\"link('_dir','free0',this)\" class=\"leftMenuLinkHeadInActive\">free</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID939\" class=\"leftMenuInActive\"><a id=\"aID939\" href=\"#\" OnMouseOver=\"link('_class','FreeController35940',this)\" class=\"leftMenuLinkInActive\">FreeController</a></div>\n");
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
