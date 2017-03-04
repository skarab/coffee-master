function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6276\" class=\"headerLeftMenuInActive\"><a id=\"aID6276\" href=\"#\" OnMouseOver=\"link('_dir','plane0',this)\" class=\"leftMenuLinkHeadInActive\">plane</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID736\" class=\"leftMenuInActive\"><a id=\"aID736\" href=\"#\" OnMouseOver=\"link('_class','Plane39014',this)\" class=\"leftMenuLinkInActive\">Plane</a></div>\n");
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
