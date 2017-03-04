function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6341\" class=\"headerLeftMenuInActive\"><a id=\"aID6341\" href=\"#\" OnMouseOver=\"link('_dir','device0',this)\" class=\"leftMenuLinkHeadInActive\">device</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6342\" class=\"leftMenuInActive\"><a id=\"aID6342\" href=\"#\" OnMouseOver=\"link('_dir','config/config0',this)\" class=\"leftMenuLinkInActive\">config</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID842\" class=\"leftMenuInActive\"><a id=\"aID842\" href=\"#\" OnMouseOver=\"link('_class','Device45182',this)\" class=\"leftMenuLinkInActive\">Device</a></div>\n");
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
