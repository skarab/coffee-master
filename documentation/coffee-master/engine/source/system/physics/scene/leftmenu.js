function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6404\" class=\"headerLeftMenuInActive\"><a id=\"aID6404\" href=\"#\" OnMouseOver=\"link('_dir','scene0',this)\" class=\"leftMenuLinkHeadInActive\">scene</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID924\" class=\"leftMenuInActive\"><a id=\"aID924\" href=\"#\" OnMouseOver=\"link('_class','Scene14855',this)\" class=\"leftMenuLinkInActive\">Scene</a></div>\n");
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
