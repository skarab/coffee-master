function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6275\" class=\"headerLeftMenuInActive\"><a id=\"aID6275\" href=\"#\" OnMouseOver=\"link('_dir','line0',this)\" class=\"leftMenuLinkHeadInActive\">line</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID735\" class=\"leftMenuInActive\"><a id=\"aID735\" href=\"#\" OnMouseOver=\"link('_class','Line339014',this)\" class=\"leftMenuLinkInActive\">Line3</a></div>\n");
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
