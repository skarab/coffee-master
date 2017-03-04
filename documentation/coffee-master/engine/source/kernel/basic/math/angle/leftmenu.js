function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6282\" class=\"headerLeftMenuInActive\"><a id=\"aID6282\" href=\"#\" OnMouseOver=\"link('_dir','angle0',this)\" class=\"leftMenuLinkHeadInActive\">angle</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID742\" class=\"leftMenuInActive\"><a id=\"aID742\" href=\"#\" OnMouseOver=\"link('_class','Angle39014',this)\" class=\"leftMenuLinkInActive\">Angle</a></div>\n");
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
