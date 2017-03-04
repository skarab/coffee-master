function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6397\" class=\"headerLeftMenuInActive\"><a id=\"aID6397\" href=\"#\" OnMouseOver=\"link('_dir','chamfer_cylinder0',this)\" class=\"leftMenuLinkHeadInActive\">chamfer_cylinder</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID916\" class=\"leftMenuInActive\"><a id=\"aID916\" href=\"#\" OnMouseOver=\"link('_class','ChamferCylinder14855',this)\" class=\"leftMenuLinkInActive\">ChamferCylinder</a></div>\n");
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
