function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6500\" class=\"headerLeftMenuInActive\"><a id=\"aID6500\" href=\"#\" OnMouseOver=\"link('_dir','source0',this)\" class=\"leftMenuLinkHeadInActive\">source</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1116\" class=\"leftMenuInActive\"><a id=\"aID1116\" href=\"#\" OnMouseOver=\"link('_class','Application56598',this)\" class=\"leftMenuLinkInActive\">Application</a></div>\n");
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
