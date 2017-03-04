function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6476\" class=\"headerLeftMenuInActive\"><a id=\"aID6476\" href=\"#\" OnMouseOver=\"link('_dir','component0',this)\" class=\"leftMenuLinkHeadInActive\">component</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1073\" class=\"leftMenuInActive\"><a id=\"aID1073\" href=\"#\" OnMouseOver=\"link('_class','Types22454',this)\" class=\"leftMenuLinkInActive\">Types</a></div>\n");
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
