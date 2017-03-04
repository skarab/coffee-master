function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6343\" class=\"headerLeftMenuInActive\"><a id=\"aID6343\" href=\"#\" OnMouseOver=\"link('_dir','sound0',this)\" class=\"leftMenuLinkHeadInActive\">sound</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID844\" class=\"leftMenuInActive\"><a id=\"aID844\" href=\"#\" OnMouseOver=\"link('_class','Sound45182',this)\" class=\"leftMenuLinkInActive\">Sound</a></div>\n");
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
